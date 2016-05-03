/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief Implementation of Othello board.
 * @file table.cpp
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include <iomanip>
#include <string>

#include "exception.h"
#include "table.h"

std::ostream &operator<<(std::ostream &os, const Table::Board &b)
{
  for (const auto &it: b.tableMatrix)
  {
    os << static_cast<int>(it);
  }
  return os << b.rows << b.cols << b.blackStones << b.whiteStones << b.moveCount;
}

/**
 * @brief Sets CLI representation of black stone.
 */
const std::string Table::CLI_BLACK_STONE = "☻";

/**
 * @brief Sets CLI representation of white stone.
 */
const std::string Table::CLI_WHITE_STONE = "☺";

/**
 * @brief Creates new board.tableMatrix with default size.
 */
Table::Table():
  Table(DEFAULT_ROWS, DEFAULT_COLS) {}

/**
 * @brief Creates new board.tableMatrix.
 */
Table::Table(int initRows, int initCols)
{
  // Number of rows and cols must meet required minimum and must be even
  if(initRows < MIN_ROWS || initCols < MIN_COLS || (initRows & 1) || (initCols & 1))
    throw OthelloError("Initial row/col count is too small or odd.");

  board.rows = initRows;
  board.cols = initCols;
  board.moveCount = 0;
  board.tableMatrix.resize(board.rows * board.cols);

  for(Stone& s : board.tableMatrix)
    s = Stone::FREE;

  // Place initial stones on board.tableMatrix
  int firstCtrRow = (board.rows >> 1) - 1;
  int firstCtrCol = (board.cols >> 1) - 1;

  std::vector<Coords> ctrWhite { std::make_pair(firstCtrRow, firstCtrCol), std::make_pair(firstCtrRow + 1, firstCtrCol + 1) };
  std::vector<Coords> ctrBlack { std::make_pair(firstCtrRow + 1, firstCtrCol), std::make_pair(firstCtrRow, firstCtrCol + 1) };

  for(const Coords& c : ctrWhite)
    board.tableMatrix[getVecIndex(c)] = Stone::WHITE;

  for(const Coords& c : ctrBlack)
    board.tableMatrix[getVecIndex(c)] = Stone::BLACK;

  board.blackStones = 2;
  board.whiteStones = 2;

  // Invalidate cache values
  clearCache();
}

int Table::getVecIndex(const Coords& coords) const
{
  return coords.first * board.cols + coords.second;
}

/**
 * @brief Determines if given stone can be placed at given coordinates.
 *        @c Stone::FREE can be put anywhere.
 */
bool Table::canPutStone(const Coords& coords, Stone stone) const
{
  if (stone == Stone::FREE)
  {
    return true;
  }

  // Check if row and col are valid
  if(coords.first < 0 || coords.first >= board.rows || coords.second < 0 || coords.second >= board.cols)
    return false;

  // Check if the requested spot is free
  if(board.tableMatrix[getVecIndex(coords)] != Stone::FREE)
    return false;

  // Only refill the cache vector if we are dealing with different coordinates or a different stone color
  if(coords != cachedCoords || stone != cachedStone)
  {
    fillCacheVector(coords, stone);

    // Set cache configuration to current values
    cachedCoords = coords;
    cachedStone = stone;
  }

  // If there are no stones we can flip it means that the stone cannot be placed on this position
  if(stoneFlipCache.empty())
    return false;
  else
    return true;
}

int Table::getRowCount() const
{
  return board.rows;
}

int Table::getColCount() const
{
  return board.cols;
}

int Table::getBlackStonesCount() const
{
  return board.blackStones;
}

int Table::getWhiteStonesCount() const
{
  return board.whiteStones;
}

/**
 * @brief Returns number of moves made.
 */
int Table::getMoveCount() const
{
  return board.moveCount;
}

/**
 * @brief Invalidates values in cache.
 */
void Table::clearCache() const
{
  stoneFlipCache.clear();
  cachedCoords = std::make_pair(-1, -1);
  cachedStone = Stone::FREE;
}

/**
 * @brief Will attempt to place stone at given coordinates.
 *        @c Stone::FREE stone can be put anywhere, also move is counted.
 *
 * @exception Will throw OthelloError if stone cannot be placed.
 */
void Table::putStone(const Coords& coords, Stone stone)
{
  if (stone == Stone::FREE)
  {
    board.moveCount++;
    return;
  }

  if(!canPutStone(coords, stone))
  {
    throw OthelloError("Cannot place stone at supplied location");
  }

  // Modify stone counters
  int flipVecSize = stoneFlipCache.size();

  if(stone == Stone::BLACK)
  {
    board.blackStones += flipVecSize + 1;
    board.whiteStones -= flipVecSize;
  }
  else
  {
    board.whiteStones += flipVecSize + 1;
    board.blackStones -= flipVecSize;
  }

  // Flip all stones in flip cache
  for(const Coords& c : stoneFlipCache)
    board.tableMatrix[getVecIndex(c)] = stone;

  // Flip current stone too
  board.tableMatrix[getVecIndex(coords)] = stone;

  // Increment move count
  board.moveCount++;
}

/**
 * @brief Returns a vector of coordinates where a stone of the given color can be placed.
 *
 * Vector will be empty if the stone cannot be placed anywhere on the board.
 */
std::vector<Table::Coords> Table::getPossibleCoords(Stone stone)
{
  // This vector will hold coordinates which we can move to
  std::vector<Coords> possibleCoords;

  for(int i = 0; i < board.rows; i++)
  {
    for(int j = 0; j < board.cols; j++)
    {
      Coords c = std::make_pair(i, j);
      if(canPutStone(c, stone))
        possibleCoords.push_back(c);
    }
  }

  return possibleCoords;
}

/**
 * @brief Returns true if it is possible to put stone on any location.
 */
bool Table::isMoveWithStonePossible(Stone stone) const
{
  for(int i = 0; i < board.rows; i++)
  {
    for(int j = 0; j < board.cols; j++)
    {
      Coords c = std::make_pair(i, j);
      if(canPutStone(c, stone))
      {
        return true;
      }
    }
  }

  return false;
}

const Table::Board &Table::getBoard() const
{
  return board;
}

void Table::setBoard(const Board &board)
{
  clearCache();
  this->board = board;
}

void Table::recountScores()
{
  board.blackStones = 0;
  board.whiteStones = 0;

  for(const Stone& s : board.tableMatrix)
  {
    if(s == Stone::BLACK)
      board.blackStones++;
    else if(s == Stone::WHITE)
      board.whiteStones++;
  }
}

void Table::fillCacheVector(const Coords& coords, Stone stone) const
{
  // Clear out current cache vector
  clearCache();

  // Try turning stones in all 8 directions
  // East
  turnStonesByVector(1, 0, coords, stone);

  // West
  turnStonesByVector(-1, 0, coords, stone);

  // South
  turnStonesByVector(0, 1, coords, stone);

  // North
  turnStonesByVector(0, -1, coords, stone);

  // South-East
  turnStonesByVector(1, 1, coords, stone);

  // South-West
  turnStonesByVector(1, -1, coords, stone);

  // Nort-East
  turnStonesByVector(-1, 1, coords, stone);

  // North-West
  turnStonesByVector(-1, -1, coords, stone);
}

void Table::turnStonesByVector(int x, int y, const Coords& startCoords, Stone ownStone) const
{
  int r;
  int c;
  int stepsMade = 0;
  bool foundOwn = false;

  // Search the board.tableMatrix in the direction specified by the direction vector
  for(r = startCoords.first + x, c = startCoords.second + y; r >= 0 && r < board.rows && c >= 0 && c < board.cols; r += x, c += y)
  {
    Coords current = std::make_pair(r, c);

    Stone stoneAtPos = board.tableMatrix[getVecIndex(current)];

    if(stoneAtPos == ownStone)
    {
      foundOwn = true;
      break;
    }
    else if(stoneAtPos == Stone::FREE)
      break;

    stepsMade++;
  }

  // Fill cache vector with stones to turn if we made a successful connection
  if(foundOwn && stepsMade > 0)
  {
    int stepCount;
    for(r = startCoords.first + x, c = startCoords.second + y, stepCount = 0; stepCount < stepsMade; r += x, c += y, stepCount++)
      stoneFlipCache.push_back(std::make_pair(r, c));
  }
}

/**
 * @brief Prints current table to stdout.
 */
void Table::print() const
{
  // Print column headers
  std::cout << "   |";

  for(int i = 0; i < board.cols; i++)
    std::cout << " " << static_cast<char>('a' + i) << " |";

  std::cout << std::endl;

  // Print the entire board.tableMatrix
  for(int i = 0; i < board.rows; i++)
  {
    std::cout << std::setw(2) << i + 1 << " |";

    for(int j = 0; j < board.cols; j++)
    {
      Coords current = std::make_pair(i, j);
      std::string res;
      switch(board.tableMatrix[getVecIndex(current)])
      {
        case Stone::FREE:
          res = " ";
          break;
        case Stone::BLACK:
          res = CLI_BLACK_STONE;
          break;
        case Stone::WHITE:
          res = CLI_WHITE_STONE;
          break;
      }

      std::cout << " " <<  res << " |";
    }

    // Print scores if we are in the middle of the board.tableMatrix
    if(i == (board.rows >> 1) - 1)
      std::cout << "\tScore(" << CLI_WHITE_STONE << "): " << board.whiteStones;
    if(i == (board.rows >> 1))
      std::cout << "\tScore(" << CLI_BLACK_STONE << "): " << board.blackStones;

    std::cout << std::endl;
  }
}

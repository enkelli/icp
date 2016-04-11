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
#include <iostream>
#include <string>

#include "exception.h"
#include "table.h"

/**
 * @brief Set CLI representation of black stone.
 */
const std::string Table::CLI_BLACK_STONE = "☻";

/**
 * @brief Set CLI representation of white stone.
 */
const std::string Table::CLI_WHITE_STONE = "☺";

/**
 * @brief Creates new board with default size.
 */
Table::Table():
  Table(defaultRows, defaultCols) {}

/**
 * @brief Creates new board.
 */
Table::Table(int initRows, int initCols)
{
  // Number of rows and cols must meet required minimum and must be even
  if(initRows < minRows || initCols < minCols || (initRows & 1) || (initCols & 1))
    throw OthelloError("Initial row/col count is too small or odd");

  rows = initRows;
  cols = initCols;
  board.resize(rows * cols);

  for(Stone& s : board)
    s = Stone::FREE;

  // Place initial stones on board
  int firstCtrRow = (rows >> 1) - 1;
  int firstCtrCol = (cols >> 1) - 1;
  
  std::vector<Coords> ctrWhite { std::make_pair(firstCtrRow, firstCtrCol), std::make_pair(firstCtrRow + 1, firstCtrCol + 1) };
  std::vector<Coords> ctrBlack { std::make_pair(firstCtrRow + 1, firstCtrCol), std::make_pair(firstCtrRow, firstCtrCol + 1) };

  for(const Coords& c : ctrWhite)
    board[getVecIndex(c)] = Stone::WHITE;

  for(const Coords& c : ctrBlack)
    board[getVecIndex(c)] = Stone::BLACK;

  blackStones = 2;
  whiteStones = 2;

  // Invalidate cache values
  cachedCoords = std::make_pair(-1, -1);
  cachedStone = Stone::FREE;
}

int Table::getVecIndex(const Coords& coords) const
{
  return coords.first * cols + coords.second;
}

/**
 * @brief Determines if given stone can be placed at given coordinates
 */
bool Table::canPut(const Coords& coords, Stone stone)
{
  // Check if row and col are valid
  if(coords.first < 0 || coords.first >= rows || coords.second < 0 || coords.second >= cols)
    return false;

  // Check if the requested spot is free
  if(board[getVecIndex(coords)] != Stone::FREE)
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

/**
 * @brief Will attempt to place stone at given coordinates.
 *
 * @exception Will throw OthelloError if stone cannot be placed
 */
void Table::putStone(const Coords& coords, Stone stone)
{
  if(!canPut(coords, stone))
    throw OthelloError("Cannot place stone at supplied location");

  // Modify stone counters
  int flipVecSize = stoneFlipCache.size();

  if(stone == Stone::BLACK)
  {
    blackStones += flipVecSize + 1;
    whiteStones -= flipVecSize;
  }
  else
  {
    whiteStones += flipVecSize + 1;
    blackStones -= flipVecSize;
  }

  // Flip all stones in flip cache
  for(const Coords& c : stoneFlipCache)
    board[getVecIndex(c)] = stone;

  // Flip current stone too
  board[getVecIndex(coords)] = stone;
}

Table::Board &Table::getBoard()
{
  return board;
}
 
void Table::setBoard(Board &board)
{
  this->board = board;
  //TODO re-count score
}


void Table::fillCacheVector(const Coords& coords, Stone stone)
{
  // Clear out current cache vector
  stoneFlipCache.clear();

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

void Table::turnStonesByVector(int x, int y, const Coords& startCoords, Stone ownStone)
{
  int r;
  int c;
  int stepsMade = 0;
  bool foundOwn = false;

  // Search the board in the direction specified by the direction vector
  for(r = startCoords.first + x, c = startCoords.second + y; r >= 0 && r < rows && c >= 0 && c < cols; r += x, c += y)
  {
    Coords current = std::make_pair(r, c);

    Stone stoneAtPos = board[getVecIndex(current)];

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
 * @brief Print current table to stdout
 */
void Table::print() const
{
  // Print column headers
  std::cout << "   |";

  for(int i = 0; i < cols; i++)
    std::cout << " " << static_cast<char>('a' + i) << " |";

  std::cout << std::endl;

  // Print the entire board
  for(int i = 0; i < rows; i++)
  {
    std::cout << std::setw(2) << i + 1 << " |";

    for(int j = 0; j < cols; j++)
    {
      Coords current = std::make_pair(i, j);
      std::string res;
      switch(board[getVecIndex(current)])
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

    // Print scores if we are in the middle of the board
    if(i == (rows >> 1) - 1)
      std::cout << "\tScore(White): " << whiteStones;
    if(i == (rows >> 1))
      std::cout << "\tScore(Black): " << blackStones; 

    std::cout << std::endl;
  }
}

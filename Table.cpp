/*
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * Authors:
 * Pavol Plaskon  - xplask00
 * Matej Postolka - xposto02
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>

#include "Table.h"

Table::Table(int initRows, int initCols)
{
  // Number of rows and cols must meet required minimum and must be even
  if(initRows < minRows || initCols < minCols || (initRows & 1) || (initCols & 1))
    throw std::invalid_argument("Initial row/col count is too small or odd");

  rows = initRows;
  cols = initCols;
  table.resize(rows * cols);

  for(int i = 0; i < (rows * cols); i++)
    table[i] = STONE_FREE;

  // Place initial stones on table
  int firstCtrRow = (rows >> 1) - 1;
  int firstCtrCol = (cols >> 1) - 1;

  table[getVecIndex(firstCtrRow, firstCtrCol)] = STONE_WHITE;
  table[getVecIndex(firstCtrRow, firstCtrCol + 1)] = STONE_BLACK;
  table[getVecIndex(firstCtrRow + 1, firstCtrCol)] = STONE_BLACK;
  table[getVecIndex(firstCtrRow + 1, firstCtrCol + 1)] = STONE_WHITE;
}

int Table::getVecIndex(int row, int col) const
{
  return row * cols + col;
}

void Table::putStone(int row, int col, Stone stone)
{
  // Check if row and col are valid
  if(row < 0 || row >= rows || col < 0 || col >= cols)
    throw std::invalid_argument("Coordinates out of range");

  // Check if the requested spot is free
  if(table[getVecIndex(row, col)] != STONE_FREE)
    throw std::invalid_argument("There already is a stone at the supplied position");

  bool placeStone = false;

  // Try turning stones in all 8 directions

  // East
  if(turnStonesByVector(1, 0, row, col, stone))
    placeStone = true;

  // West
  if(turnStonesByVector(-1, 0, row, col, stone))
    placeStone = true;

  // South
  if(turnStonesByVector(0, 1, row, col, stone))
    placeStone = true;

  // North
  if(turnStonesByVector(0, -1, row, col, stone))
    placeStone = true;

  // South-East
  if(turnStonesByVector(1, 1, row, col, stone))
    placeStone = true;

  // South-West
  if(turnStonesByVector(1, -1, row, col, stone))
    placeStone = true;

  // Nort-East
  if(turnStonesByVector(-1, 1, row, col, stone))
    placeStone = true;

  // North-West
  if(turnStonesByVector(-1, -1, row, col, stone))
    placeStone = true;

  // If we have managed to turn at least one direction, turn current stone as well
  if(placeStone)
    table[getVecIndex(row, col)] = stone;
  else
    throw std::invalid_argument("Cannot place stone at given coordinates");
}

bool Table::turnStonesByVector(int x, int y, int startRow, int startCol, Stone ownStone)
{
  int r;
  int c;
  int stepsMade = 0;
  bool foundOwn = false;

  // Search the table in the direction specified by the direction vector
  for(r = startRow + x, c = startCol + y; r >= 0 && r < rows && c >= 0 && c < cols; r += x, c += y)
  {
    Stone stoneAtPos = table[getVecIndex(r, c)];

    if(stoneAtPos == ownStone)
    {
      foundOwn = true;
      break;
    }
    else if(stoneAtPos == STONE_FREE)
      break;

    stepsMade++;
  }

  // Turn enemy stones if we managed to connect a friendly stone
  if(foundOwn && stepsMade > 0)
  {
    int stepCount;
    for(r = startRow + x, c = startCol + y, stepCount = 0; stepCount < stepsMade; r += x, c += y, stepCount++)
      table[getVecIndex(r, c)] = ownStone;

    return true;
  }
  else
    return false;
}

void Table::print() const
{
  // Print column headers
  std::cout << "   |";

  for(int i = 0; i < cols; i++)
    std::cout << " " << static_cast<char>('a' + i) << " |";

  std::cout << std::endl;

  // Print the entire table
  for(int i = 0; i < rows; i++)
  {
    std::cout << std::setw(2) << i + 1 << " |";

    for(int j = 0; j < cols; j++)
    {
      std::string res;
      switch(table[getVecIndex(i, j)])
      {
        case STONE_FREE:
          res = " ";
          break;
        case STONE_BLACK:
          res = "☻";
          break;
        case STONE_WHITE:
          res = "☺";
          break;
      }

      std::cout << " " <<  res << " |";
    }

    std::cout << std::endl;
  }
}

// FIXME
/* TEMPORARY SHIT */
int main()
{
  int x, y;
  std::cout << "Enter number of rows, nigger!" << std::endl;
  std::cin >> x;
  std::cout << "Enter number of cols, nigger!" << std::endl;
  std::cin >> y;
  std::cout << std::endl;

  Table t(x, y);

  while(1)
  {
    t.print();

    std::string color;
    char c;
    int row;
    int col;

    std::cout << std::endl << "Place what? (b/w): ";
    std::cin >> color;
    std::cout << "Row: ";
    std::cin >> row;
    std::cout << "Col: ";
    std::cin >> c;

    row--;
    col = static_cast<int>(c) - static_cast<int>('a');

    try
    {
      color == "b" ? t.putStone(row, col, Table::STONE_BLACK) : t.putStone(row, col, Table::STONE_WHITE);
    }
    catch(const std::invalid_argument& e)
    {
      std::cout << e.what();
    }

    std::cout << "\n\n";
  }

  return 0;
}

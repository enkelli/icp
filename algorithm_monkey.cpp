/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief Artificial intelligence which is as smart as a monkey.
 * @file algorithm_monkey.cpp
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "table.h"
#include "algorithm_monkey.h"

Table::Coords AI_Monkey::nextMove(const std::shared_ptr<Table> table) const
{
  const Table::Board board = table->getBoard();
  std::vector<Table::Coords> availableCoords;

  for(int i = 0; i < board.rows; i++)
  {
    for(int j = 0; j < board.cols; j++)
    {
      Table::Coords c = std::make_pair(i, j);
      if(board.tableMatrix[table->getVecIndex(c)] == Table::Stone::FREE)
        availableCoords.push_back(c);
    }
  }

  while(!availableCoords.empty())
  {
    std::srand(std::time(0));
    int index = std::rand() % availableCoords.size();
    if(table->canPutStone(availableCoords[index], Table::Stone::WHITE))
    {
      std::srand(std::time(0));
      int sleep = (std::rand() & 2047) + 200;
      std::cout << "The monkey is thinking..." << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
      return availableCoords[index];
    }
    else
      availableCoords.erase(availableCoords.begin()+index);
  }

  return std::make_pair(-1, -1);
}

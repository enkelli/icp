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

#include "algorithm_monkey.h"
#include "exception.h"
#include "table.h"

/**
 * @brief Returns coordinates of next @c AI move.
 *
 * @throw OthelloAIError if there are no possible moves.
 */
Table::Coords AlgorithmMonkey::nextMove(const std::shared_ptr<Table> &table, Table::Stone stone) const
{
  std::vector<Table::Coords> availableCoords = table->getPossibleCoords(stone);
  
  if(availableCoords.size() == 0)
    throw OthelloAIError("AI has no possible moves");
  
  // Get random index into available coordinates
  std::srand(std::time(0));
  int index = std::rand() % availableCoords.size();
  
  // Random sleep
  std::srand(std::time(0));
  int sleep = (std::rand() & 2047) + 200;
  
  std::cout << "The monkey is thinking..." << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(sleep));

  return availableCoords[index];
}

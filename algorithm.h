/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief An abstract class for algorithm implementing Othello player
 * @file algorithm.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */
 
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <memory>

#include "table.h"

/**
 * @brief An abstract class for algorithm implementing Othello player.
 */
class Algorithm
{
  public:
    virtual ~Algorithm() = default;
    virtual Table::Coords nextMove(const std::shared_ptr<Table> &table, Table::Stone stone) const = 0;
};

#endif

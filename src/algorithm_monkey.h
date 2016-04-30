/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief A monkey algorithm
 * @file algorithm_monkey.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#ifndef ALGORITHM_MONKEY_H
#define ALGORITHM_MONKEY_H

#include "algorithm.h"

/**
 * @brief An abstract class for algorithm implementing Othello player.
 */
class AlgorithmMonkey : public Algorithm
{
  public:
    AlgorithmMonkey() = default;

    virtual Table::Coords nextMove(const std::shared_ptr<Table> &table, Table::Stone stone) const override;
};

#endif

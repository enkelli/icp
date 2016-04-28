/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief A chimpanzee algorithm
 * @file algorithm_chimpanzee.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */
 
#ifndef ALGORITHM_CHIMPANZEE_H
#define ALGORITHM_CHIMPANZEE_H

#include "algorithm.h"

/**
 * @brief An abstract class for algorithm implementing Othello player.
 */
class AlgorithmChimpanzee : public Algorithm
{
  public:
    AlgorithmChimpanzee() = default;

    virtual Table::Coords nextMove(const std::shared_ptr<Table> &table, Table::Stone stone) const override;
};

#endif

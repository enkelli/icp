/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief Representation of algorithm random class.
 * @file algorithm_random.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#ifndef ALGORITHM_RANDOM_H
#define ALGORITHM_RANDOM_H

#include "algorithm.h"

/**
 * @brief Computer algorithm playing Othello game.
 */
class AlgorithmRandom: public Algorithm
{
  public:
    virtual Table::Coords step(const Table &table) const override;
};

#endif

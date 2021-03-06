/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief Implementation of command manager.
 * @file game.cpp
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include "algorithm.h"
#include "game.h"
#include "table.h"

/**
 * @brief Creates new game.
 */
Game::Game(const std::shared_ptr<Table> &table, bool againstAI, AIPlayer PC):
  table(table), againstAI(againstAI), PC(PC) {}

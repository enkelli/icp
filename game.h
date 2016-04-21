/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief A representation of Othello game.
 * @file game.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#ifndef GAME_H
#define GAME_H

#include "command_manager.h"

class Table;

/**
 * @brief A representation of Othello game.
 */
struct Game
{
  Game(const std::shared_ptr<Table> &table, bool AI = false);

  /// Table used in current game.
  std::shared_ptr<Table> table;
  /// Command manager to save moves history.
  CommandManager cmdManager;
  /// True if player plays against PC.
  bool AIPlayer;
};

#endif

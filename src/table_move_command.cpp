/**+
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief implementation of table move command.
 * @file table_move_command.cpp
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include "table_move_command.h"

/**
 * @brief Creates a new table move command.
 */
TableMoveCommand::TableMoveCommand(
  std::shared_ptr<Table> table, Table::Coords coords, Table::Stone stone):
    table(table), board(table->getBoard()), coords(coords), stone(stone) {} 

/**
 * @brief Executes move command.
 *
 * It should be sure that command succeeds - stone can be placed on position,
 * otherwise empty command would be stored to history.
 */
void TableMoveCommand::execute()
{
  table->putStone(coords, stone);
}

/**
 * @brief One step back in game.
 */
void TableMoveCommand::undo()
{
  table->setBoard(board);
}

/**
 * @brief one step forward.
 *
 * Available only after undo.
 */
void TableMoveCommand::redo()
{
  table->setBoard(board);
  table->putStone(coords, stone);
}

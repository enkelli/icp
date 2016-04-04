 /*
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

/*
 * @brief Creates a new table move command.
 */
TableMoveCommand(table, player, move):
    table(table). player(player), move(move) {}

/*
 * @brief Executes move command.
 *
 * It should be sure that command succeeds - stone can be placed on position,
 * otherwise empty command would be stored to history.
 */
void execute()
{
    map = table->getMap;
    table->step(player, move);
}

/*
 * @brief One step back in game.
 */
void undo()
{
    Table->revertStep(player, move);   
}

/*
 * @brief one step forward.
 *
 * Avaliable only after undo.
 */
void redo()
{
    table->nextStep(player, move);
}

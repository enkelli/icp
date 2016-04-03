/*
 * @file TableMoveCommand.cpp
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief Implementation of command design patter for undo-redo actions in Othello game.
 */
 
#include "TableMoveCommand.h"

TableMoveCommand(table, player, move):
    table(table). player(player), move(move) {}

void execute()
{
    map = table->getMap;
    table->step(player, move);
}

void undo()
{
    Table->revertStep(player, move);   
}

void redo()
{
    table->nextStep(player, move);
}

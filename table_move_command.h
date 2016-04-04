/*
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief A representation of table move command.
 * @file table_move_command.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include "command.h"

/*
 * @brief A representation of table move command.
 */
class TableMoveCommand: public Command
{
    public:
        TableMoveCommand(table, player, move);
        //store table and player, perform move

        virtual void execute() override;
        virtual void undo() override;
        virtual void redo override;

    private:
        player player;
        tableObject *table; //no need to whole table object, just board..??
        Coords move;

        tableMap map;
};

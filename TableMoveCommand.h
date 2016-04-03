/*
 * @file TableMoveCommand.h
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief Command design patter for undo-redo actions in Othello game.
 */
 
#include "command.h"

/*
 * @brief Command design patter for undo-redo actions in Othello game.
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

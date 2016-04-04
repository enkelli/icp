/*
 * @file Command.h
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief Abstract class for Command design patter for undo-redo actions in Othello game.
 */
 
/*
 * @brief Abstract class for Command design patter for undo-redo actions in Othello game.
 */
class Command
{
    public:
        virtual void execute() = 0;
        virtual void undo() = 0;
        virtual void redo = 0;
};

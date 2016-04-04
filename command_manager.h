/*
 * @file CommandManager.h
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief Command manager for undo-redo actions in Othello game.
 */
 
#include <stack.h>

#include "command.h"

/*
 * @brief Command manager for undo-redo actions in Othello game.
 */
class CommandManager
{
    public:
        CommandManager();

        void executeCmd(std::shared_ptr<Command> &command);
        void undo();
        void redo();

    private:
        using CmdStack = std::stack<std::shared_ptr<Command>>;
        CmdStack undoStack;
        CmdStack redoStack;
};

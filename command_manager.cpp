/*
 * @file CommandManager.cpp
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief Implementation of command manager for undo-redo actions in Othello game.
 */
 
#include <stack.h>

#include "command_manager.h"

/*
 * @brief Creates new CommandManager.
 */
CommandManager::CommandManager() = default;


void executeCmd(std::shared_ptr<Command> &command)
{
    redoStack = CmdStack();
    command->execute();
    undoStack.push(command);
}

void undo()
{
    if (!undoStack.empty())
    {
        undoStack.top()->undo();
        redoStack.push(undoStack.top());
        undoStack.pop();        
    }
}

void redo()
{
    if (!redoStack.empty())
    {
        redoStack.top()->redo();
        undoStack.push(redoStack.top());
        redoStack.pop();
    }
}

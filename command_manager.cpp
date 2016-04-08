/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief Implementation of command manager.
 * @file command_manager.cpp
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include <stack.h>

#include "command_manager.h"

/**
 * @brief Creates new CommandManager.
 */
CommandManager::CommandManager() = default;

/**
 * @brief Executes new command.
 *
 * Executing new command deletes @c redo history.
 */
void executeCmd(std::shared_ptr<Command> &command)
{
  redoStack = CmdStack();
  command->execute();
  undoStack.push(command);
}

/**
 * @brief Returns to previous state.
 */
void undo()
{
  if (!undoStack.empty())
  {
    undoStack.top()->undo();
    redoStack.push(undoStack.top());
    undoStack.pop();        
  }
}

/**
 * @brief Forward one step in history.
 */
void redo()
{
  if (!redoStack.empty())
  {
    redoStack.top()->redo();
    undoStack.push(redoStack.top());
    redoStack.pop();
  }
}

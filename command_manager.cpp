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
void CommandManager::executeCmd(std::shared_ptr<Command> command)
{
  redoStack = CmdStack();
  command->execute();
  undoStack.push(command);
}

/**
 * @brief Returns to previous state.
 */
void CommandManager::undo()
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
void CommandManager::redo()
{
  if (!redoStack.empty())
  {
    redoStack.top()->redo();
    undoStack.push(redoStack.top());
    redoStack.pop();
  }
}

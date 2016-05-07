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
#include "table_move_command.h"

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
  undoStack.emplace_back(command);
}

/**
 * @brief Returns game board to previous state.
 */
void CommandManager::undo()
{
  if (!undoStack.empty())
  {
    undoStack.back()->undo();
    redoStack.emplace_back(undoStack.back());
    undoStack.pop_back();
  }
}

/**
 * @brief Forward game board one step in history.
 */
void CommandManager::redo()
{
  if (!redoStack.empty())
  {
    redoStack.back()->redo();
    undoStack.emplace_back(redoStack.back());
    redoStack.pop_back();
  }
}

/**
 * @brief Returns coords stored for @c undo operations.
 */
std::vector<Table::Coords> CommandManager::getUndoCoords() const
{
  std::vector<Table::Coords> coords;
  for (auto c: undoStack)
  {
    if (c->isTableMoveCommand())
    {
      coords.emplace_back((std::static_pointer_cast<TableMoveCommand>(c))->getCoords());
    }
  }
  return coords;
}

/**
 * @brief Returns coords stored for @c redo operations.
 */
std::vector<Table::Coords> CommandManager::getRedoCoords() const
{
  std::vector<Table::Coords> coords;
  for (auto c: redoStack)
  {
    if (c->isTableMoveCommand())
    {
      coords.emplace_back((std::static_pointer_cast<TableMoveCommand>(c))->getCoords());
    }
  }
  return coords;
}

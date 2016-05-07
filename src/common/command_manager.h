/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief A representation of command manager.
 * @file command_manager.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include <memory>
#include <vector>

#include "command.h"
#include "table.h"

/**
 * @brief Command manager for undo-redo actions in Othello game.
 */
class CommandManager
{
  public:
    CommandManager();

    void executeCmd(std::shared_ptr<Command> command);
    void undo();
    void redo();

    /// Undo serialization
    std::vector<Table::Coords> getUndoCoords() const;
    /// Redo serialization
    std::vector<Table::Coords> getRedoCoords() const;

  private:
    using CmdStack = std::vector<std::shared_ptr<Command>>;
    /// Stack for previous move commands.
    CmdStack undoStack;
    /// Stack for forward move commands.
    CmdStack redoStack;
};

#endif

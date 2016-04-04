/*
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

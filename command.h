/*
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief Representation of command.
 * @file command.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#ifndef COMMAND_H
#define COMMAND_H

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

#endif

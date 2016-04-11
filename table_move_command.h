/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief A representation of table move command.
 * @file table_move_command.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#ifndef TABLE_MOVE_COMMAND_H
#define TABLE_MOVE_COMMAND_H

#include <memory>

#include "command.h"
#include "table.h"

/**
 * @brief A representation of table move command.
 */
class TableMoveCommand: public Command
{
  public:
    TableMoveCommand(std::shared_ptr<Table> table, Table::Coords coords, Table::Stone stone);

    virtual void execute() override;
    virtual void undo() override;
    virtual void redo() override;

  private:
    std::shared_ptr<Table> table;
    const Table::Board board;
    Table::Coords coords;
    Table::Stone stone;
};

#endif

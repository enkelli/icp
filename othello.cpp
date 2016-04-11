/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief A representation of Othello brain.
 * @file othello.cpp
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include <cctype>
#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "command_manager.h"
#include "exception.h"
#include "othello.h"
#include "table.h"
#include "table_move_command.h"
#include "algorithm.h"
#include "algorithm_monkey.h"

Othello::Othello() = default;

void Othello::play()
{                     
  std::cout << "Welcome to the Othello." << std::endl;
  printCliHelp();

  unsigned size = getInitSize();

  auto table = std::make_shared<Table>(size, size);
  CommandManager cmdManager;

  const std::vector<std::string> players{Table::CLI_BLACK_STONE, Table::CLI_WHITE_STONE};

  std::string input;

  table->print();

  while(1)        
  {               
    std::cout << std::endl << "On turn: " << players[table->getMoveCount() & 1]  << " " << std::endl;

    Algorithm* algo = new AI_Monkey();

    if (table->getMoveCount() & 1)
    {
      auto moveCmd = std::make_shared<TableMoveCommand>(table, algo->nextMove(table), Table::Stone::WHITE);
      cmdManager.executeCmd(moveCmd);
      table->print();
      std::cout << std::endl;
      continue;
    }

    std::cout << ">>";
    std::cin >> input;

    if (input == "H" || input == "help")
    {
      printCliHelp();
      continue;
    }
    else if (input == "u" || input == "undo")
    {
      cmdManager.undo();
      table->print();
      std::cout << std::endl; 
    }
    else if (input == "r" || input == "redo")
    {
      cmdManager.redo();
      table->print();
      std::cout << std::endl; 
    }
    else if (input == "x" || input == "exit")
    {
      std::cout << "Good bye!" << std::endl;
      return;
    }
    else if (input.size() > 1 && isalpha(input[0]) && isdigit(input[1]))
    {
      char c = input[0];
      int row = input[1] - '0';
      int col;
      row--;
      col = static_cast<int>(c) - static_cast<int>('a');

      Table::Coords coords = std::make_pair(row, col);
      if (table->canPutStone(coords, Table::Stone::BLACK))
      {
        auto moveCmd = std::make_shared<TableMoveCommand>(table, coords, Table::Stone::BLACK);
        cmdManager.executeCmd(moveCmd);
      }
      else
      {
        std::cout << "Cannot place stone at supplied location." << std::endl;
      }

    }
    else
    {
      std::cout << "\nHey man, are you fucking kidding me? RTFM!! (enter {H|help})" << std::endl;
    }
    table->print();
    std::cout << std::endl; 
  }
}

void Othello::printCliHelp() const
{
  std::cout << "Game controls:" << std::endl;
  std::cout << "\t H | help --> print this help message" << std::endl;
  std::cout << "\t u | undo --> undo one step backward" << std::endl;
  std::cout << "\t r | redo --> redo one step forward" << std::endl;
  std::cout << "\t x | exit --> exit game" << std::endl;
  std::cout << "\t AN --> A is letter for column and N is number of row" << std::endl;
  std::cout << std::endl;
}

unsigned Othello::getInitSize() const
{
  unsigned size;
  while(true)
  {
    std::cout << "Enter size of board - 6, 8, 10 or 12!" << std::endl;
    std::cout << ">>";
    std::cin >> size;
    std::cout << std::endl;

    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Oh, I don't understand your language, try arabic numerals." << std::endl;
      continue;
    }

    if (size == 6 || size == 8 || size == 10 || size == 12)
    {
      break;
    }
    std::cout << "Wrong size! 6, 8, 10 or 12" << std::endl;
  }
  return size;
}

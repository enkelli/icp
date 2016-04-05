/*
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
#include <string>

#include "exception.h"
#include "othello.h"
#include "table.h"

Othello::Othello() = default;

void Othello::play()
{                     
  std::cout << "Welcome to the Othello." << std::endl;
  printCliHelp();

  unsigned size = getInitSize();
              
  Table table(size, size);
  int player_index = 0;
  const std::vector<std::string> players{Table::CLI_BLACK_STONE, Table::CLI_WHITE_STONE};

  std::string input;

  table.print();

  while(1)        
  {               
    std::cout << std::endl << "On turn: " << players[player_index & 1]  << " " << std::endl;
    std::cout << ">>";

    std::cin >> input;

    if (input == "H" || input == "help")
    {
      printCliHelp();
      continue;
    }
    else if (input == "u" || input == "undo")
    {
      std::cout << "You wish to undo, but authors are too lazy." << std::endl;
    }
    else if (input == "r" || input == "redo")
    {
      std::cout << "You wish to redo, but authors are too lazy." << std::endl;
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

      try
      {
        (player_index++ & 1) ?
          table.putStone(row, col, Table::Stone::WHITE) :
          table.putStone(row, col, Table::Stone::BLACK);
      }
      catch(const OthelloError& e)
      {
        std::cout << e.what();
        player_index--;
      }
      
      table.print();
      std::cout << std::endl; 
    }
    else
    {
      std::cout << "\nHey man, are you fucking kidding me? RTFM!! (enter {H|help})" << std::endl;
    }
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

    if (size == 6 || size == 8 || size == 10 || size == 12)
    {
      break;
    }
    std::cout << "Wrong size! 6, 8, 10 or 12" << std::endl;
  }
  return size;
}

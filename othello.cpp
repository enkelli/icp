/*
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * Authors:
 * Pavol Plaskon  - xplask00
 * Matej Postolka - xposto02
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>

#include "othello.h"

Othello::Othello() = default;

void Othello::play()
{                     
  unsigned size = getInitSize();
              
  Table table(size, size);
  std::vector<std::string> players{"☻", "☺"};
  int player_index = 0;

  while(1)        
  {               
    table.print();

    char c;
    int row;
    int col;

    std::cout << std::endl << "On turn: " << players[player_index & 1] << std::endl;
    std::cout << "Enter col and row: ";
    std::cin >> c >> row;

    row--;
    col = static_cast<int>(c) - static_cast<int>('a');

    try
    {
      (player_index++ & 1) ?
        table.putStone(row, col, Table::STONE_WHITE) :
        table.putStone(row, col, Table::STONE_BLACK);
    }
    catch(const std::invalid_argument& e)
    {
      std::cout << e.what();
      player_index--;
    }

    std::cout << "\n\n";
  }
}
  
unsigned Othello::getInitSize() const
{
  unsigned size;
  while(true)
  {
    std::cout << "Enter size of board - 6, 8, 10 or 12!" << std::endl;
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

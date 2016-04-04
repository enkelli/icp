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

#include "Othello.h"

Othello::Othello() = default;

void Othello::play()
{
  /*
  int x, y;
  std::cout << "Enter number of rows, nigger!" << std::endl;
  std::cin >> x;
  std::cout << "Enter number of cols, nigger!" << std::endl;
  std::cin >> y;
  std::cout << std::endl;

  Table table(x, y);
  */
  Table table;

  while(1)
  {
    table.print();

    std::string color;
    char c;
    int row;
    int col;

    std::cout << std::endl << "Place what? (b/w): ";
    std::cin >> color;
    std::cout << "Row: ";
    std::cin >> row;
    std::cout << "Col: ";
    std::cin >> c;

    row--;
    col = static_cast<int>(c) - static_cast<int>('a');

    try
    {
      color == "b" ?
          table.putStone(row, col, Table::STONE_BLACK) :
          table.putStone(row, col, Table::STONE_WHITE);
    }
    catch(const std::invalid_argument& e)
    {
      std::cout << e.what();
    }

    std::cout << "\n\n";
  }
}

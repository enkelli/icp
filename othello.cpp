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
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "algorithm.h"
#include "algorithm_monkey.h"
#include "command_manager.h"
#include "exception.h"
#include "game.h"
#include "othello.h"
#include "table.h"
#include "table_move_command.h"

Othello::Othello() = default;

void Othello::play()
{                     
  startNewGame();

  const std::vector<std::string> players{Table::CLI_BLACK_STONE, Table::CLI_WHITE_STONE};

  std::string input;

  games[currGame].table->print();
    
  std::unique_ptr<AI_Monkey> algo(new AI_Monkey());

  while(1)        
  {               
    std::cout << std::endl << "On turn: " << players[games[currGame].table->getMoveCount() & 1]  << " " << std::endl;

    if (games[currGame].table->getMoveCount() & 1)
    {
      if (games[currGame].AIPlayer)
      {
        auto moveCmd = std::make_shared<TableMoveCommand>(
            games[currGame].table,
            algo->nextMove(games[currGame].table, Table::Stone::WHITE),
            Table::Stone::WHITE
          );
        games[currGame].cmdManager.executeCmd(moveCmd);
        games[currGame].table->print();
        std::cout << std::endl;
        continue;
      }
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
      games[currGame].cmdManager.undo();
      games[currGame].table->print();
      std::cout << std::endl; 
    }
    else if (input == "r" || input == "redo")
    {
      games[currGame].cmdManager.redo();
      games[currGame].table->print();
      std::cout << std::endl; 
    }
    else if (input == "s" || input == "save")
    {
      std::string fileName;
      std::cout << "Enter file name: ";
      std::cin >> fileName;
      std::cout << "Game saved to: " << fileName << std::endl;
  
      saveGame(fileName);
    }
    else if (input == "load")
    {
      std::string fileName;
      std::cout << "Enter file name: ";
      std::cin >> fileName;
  
      loadGame(fileName);
      std::cout << "Game loaded from: " << fileName << std::endl;
    }
    else if (input == "x" || input == "exit")
    {
      closeCurrentGame();
      if (games.empty())
      {
        std::cout << "Good bye!" << std::endl;
        return;
      }
      std::cout << "\tClosing game " << currGame + 2 << std::endl << std::endl;
    }
    else if (input == "n" || input == "new")
    {
      std::cout << "Starting next game. Opened games: " << games.size() + 1 << std::endl;
      startNewGame();
    }
    else if (input == "switch")
    {
      std::string indexStr;
      std::cin >> indexStr;
      if (!isdigit(indexStr[0]))
      {
        continue;
      }
      unsigned index = std::stoi(indexStr); // first is int, don't care about rest
      std::cout << "Switching to  game " << index << std::endl;
      currGame = index - 1;
    }
    else if (input.size() > 1 && isalpha(input[0]) && isdigit(input[1]))
    {
      char c = input[0];
      int row = input[1] - '0';
      int col;
      row--;
      col = static_cast<int>(c) - static_cast<int>('a');

      Table::Coords coords = std::make_pair(row, col);
      Table::Stone currStone = games[currGame].table->getMoveCount() & 1 ?
        Table::Stone::WHITE : Table::Stone::BLACK;

      if (games[currGame].table->canPutStone(coords, currStone))
      {
        auto moveCmd = std::make_shared<TableMoveCommand>(games[currGame].table, coords, currStone);
        games[currGame].cmdManager.executeCmd(moveCmd);
      }
      else
      {
        std::cout << "Cannot place stone at supplied location." << std::endl;
      }

    }
    else
    {
      std::cout << "\nHey man, are you kidding me? RTFM!! (enter {H|help})" << std::endl;
    }
    std::cout << std::endl;
    games[currGame].table->print();
    std::cout << std::endl; 
  }
}

void Othello::startNewGame()
{
  std::cout << "\tWelcome to the Othello." << std::endl;
  printCliHelp();

  unsigned size = getInitSize();
  bool againstAI = chooseOpponentAI();

  auto table = std::make_shared<Table>(size, size);
  CommandManager cmdM;
  games.emplace_back(table, cmdM, againstAI);
  currGame = games.size() - 1;
}

void Othello::closeCurrentGame()
{
  games.erase(games.begin() + currGame);
  if (currGame > 0)
  {
    currGame--;
  }
}

void Othello::printCliHelp() const
{
  std::cout << "Game controls:" << std::endl;
  std::cout << "\t H | help --> print this help message" << std::endl;
  std::cout << "\t u | undo --> undo one step backward" << std::endl;
  std::cout << "\t r | redo --> redo one step forward" << std::endl;
  std::cout << "\t n | new  --> start next game" << std::endl;
  std::cout << "\t load     --> load saved game" << std::endl;
  std::cout << "\t s | save --> save current game" << std::endl;
  std::cout << "\t x | exit --> exit game" << std::endl;
  std::cout << "\t AN --> A is letter for column and N is number of row" << std::endl;
  std::cout << std::endl;
}

bool Othello::chooseOpponentAI() const
{
  std::cout << "Do you wanna play against computer? (y/n)" << std::endl;
  std::cout << ">>";
  std::string answer;
  std::cin >> answer;
  return tolower(answer[0]) == 'y';
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

void Othello::saveGame(const std::string &fileName) const
{
  Table::Board board = games[currGame].table->getBoard();

  std::ofstream ofs(fileName);
  boost::archive::text_oarchive oa(ofs);
  oa << board;
}

void Othello::loadGame(const std::string &fileName)
{
  Table::Board board;

  std::ifstream ifs(fileName);
  boost::archive::text_iarchive ia(ifs);
  ia >> board;

  games[currGame].table->setBoard(board);
}

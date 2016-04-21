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

#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"

#include "algorithm.h"
#include "algorithm_monkey.h"
#include "command_manager.h"
#include "exception.h"
#include "game.h"
#include "othello.h"
#include "table_move_command.h"

/**
 * @brief Creates new Othello object.
 */
Othello::Othello() = default;

/**
 * @brief Main function that controls whole CLI gameplay.
 */
void Othello::playCli()
{                     
  startNewGameCli();

  const std::vector<std::string> players{Table::CLI_BLACK_STONE, Table::CLI_WHITE_STONE};

  std::string input;

  games[currGame].table->print();
    
  std::unique_ptr<AlgorithmMonkey> algo(new AlgorithmMonkey());

  while(1)        
  {               
    std::cout << std::endl << "On turn: " << players[games[currGame].table->getMoveCount() & 1]  << " " << std::endl;

    if (games[currGame].table->getMoveCount() & 1)
    {
      if (games[currGame].AIPlayer)
      {
        Table::Coords coords = algo->nextMove(games[currGame].table, Table::Stone::WHITE);
        putStoneIfPossible(coords, Table::Stone::WHITE);
        games[currGame].table->print();
        std::cout << std::endl;
        continue;
      }
    }

    std::cout << ">>";
    std::cin >> input;

    if (input == "H" || input == "help")
    {
      printHelpCli();
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
    else if (input == "reset")
    {
      resetCurrentGame();
    }
    else if (input == "s" || input == "save")
    {
      std::string fileName;
      std::cout << "Enter file name: ";
      std::cin >> fileName;
  
      if (saveGame(fileName))
      {     
        std::cout << "Game saved to: " << fileName << std::endl;
      }
      else
      {
        std::cout << "ERROR: Cannot save game to: " << fileName << std::endl;
      }

    }
    else if (input == "load")
    {
      std::string fileName;
      std::cout << "Enter file name: ";
      std::cin >> fileName;
  
      if (loadGame(fileName))
      {
        std::cout << "Game loaded from: " << fileName << std::endl;
      }
      else
      {
        std::cout << "ERROR: Cannot load game from: " << fileName << std::endl;
      }

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
      startNewGameCli();
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

      if (!putStoneIfPossible(coords, currStone))
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

/**
 * @brief Asks user about parameters for new game and start new game.
 */
void Othello::startNewGameCli()
{
  std::cout << "\tWelcome to the Othello." << std::endl;
  printHelpCli();

  unsigned size = getInitSizeCli();
  bool againstAI = chooseOpponentAICli();

  startNewGame(size, againstAI);
}

void Othello::printHelpCli() const
{
  std::cout << "Game controls:" << std::endl;
  std::cout << "\t H | help --> print this help message" << std::endl;
  std::cout << "\t u | undo --> undo one step backward" << std::endl;
  std::cout << "\t r | redo --> redo one step forward" << std::endl;
  std::cout << "\t reset    --> resets current game to start state" << std::endl;
  std::cout << "\t n | new  --> start next game" << std::endl;
  std::cout << "\t load     --> load saved game" << std::endl;
  std::cout << "\t s | save --> save current game" << std::endl;
  std::cout << "\t x | exit --> exit game" << std::endl;
  std::cout << "\t AN --> A is letter for column and N is number of row" << std::endl;
  std::cout << std::endl;
}

/**
 * @brief Asks user whether wants to play against pc
 *
 * @return True if wants to play against PC, @c false otherwise.
 */
bool Othello::chooseOpponentAICli() const
{
  std::cout << "Do you wanna play against computer? (y/n)" << std::endl;
  std::cout << ">>";
  std::string answer;
  std::cin >> answer;
  return tolower(answer[0]) == 'y';
}

/**
 * @brief Asks user for table size.
 */
unsigned Othello::getInitSizeCli() const
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

/**
 * @brief Starts new game alongside currently opened games.
 */
void Othello::startNewGame(unsigned size, bool againstAI)
{  
  auto table = std::make_shared<Table>(size, size);
  games.emplace_back(table, againstAI);
  currGame = games.size() - 1;
}

/**
 * @brief Ends current game and previous one becomes active.
 */
void Othello::closeCurrentGame()
{
  games.erase(games.begin() + currGame);
  if (currGame > 0)
  {
    currGame--;
  }
}

void Othello::resetCurrentGame()
{
  int oldRows = games[currGame].table->getRowsCount();
  int oldCols = games[currGame].table->getColsCount();
  auto table = std::make_shared<Table>(oldRows, oldCols);

  games[currGame] = Game(table, games[currGame].AIPlayer);
}

/**
 * @brief Tries to put stone on supplied coordinates.
 *
 * @return Returns @c true if stone was put, @c false otherwise.
 */
bool Othello::putStoneIfPossible(Table::Coords coords, Table::Stone stone)
{
  if (games[currGame].table->canPutStone(coords, stone))
  {
    auto moveCmd = std::make_shared<TableMoveCommand>(games[currGame].table, coords, stone);
    games[currGame].cmdManager.executeCmd(moveCmd);
    return true;
  }
  return false;  
}

/**
 * @brief Loads table status from file and sets it on current table.
 *
 * @return True on successful load, @c false otherwise.
 */
bool Othello::loadGame(const std::string &fileName)
{
  Table::Board board;

  std::ifstream ifs(fileName);
  try
  {
    boost::archive::text_iarchive ia(ifs);
    ia >> board;
  }
  catch(boost::archive::archive_exception)
  {
    return false;
  }

  games[currGame].table->setBoard(board);
  return true;
}

/**
 * @brief Saves current table status to file.
 *
 * @return True on successful save, @c false otherwise.
 */
bool Othello::saveGame(const std::string &fileName) const
{
  Table::Board board = games[currGame].table->getBoard();

  std::ofstream ofs(fileName);
  try
  {
    boost::archive::text_oarchive oa(ofs);
    oa << board;
  }
  catch(boost::archive::archive_exception)
  {
    return false;
  }

  return true;
}

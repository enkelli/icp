/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief A representation of Othello brain.
 * @file othello_cli.cpp
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

#include "algorithm.h"
#include "algorithm_monkey.h"
#include "command_manager.h"
#include "exception.h"
#include "game.h"
#include "othello_cli.h"
#include "table_move_command.h"

/**
 * @brief Creates new Othello object.
 */
OthelloCli::OthelloCli() = default;

/**
 * @brief Main function that controls whole CLI gameplay.
 */
void OthelloCli::playCli()
{
  try
  {
    startNewGameCli();
  }
  catch (const OthelloError &e)
  {
    std::cout << e.what() << std::endl;
    return;
  }

  const std::vector<std::string> players{Table::CLI_BLACK_STONE, Table::CLI_WHITE_STONE};

  std::string input;

  games[currGame].table->print();

  unsigned openedGames;
  while(1)
  {
    if ((openedGames = getOpenedGamesCount()) > 1)
    {
      std::cout << "Opened games: " << openedGames << std::endl;
    }
    std::cout << std::endl << "On turn: " << players[games[currGame].table->getMoveCount() & 1]  << " " << std::endl;

    Table::Stone currStone = games[currGame].table->getMoveCount() & 1 ?
                               Table::Stone::WHITE : Table::Stone::BLACK;

    if (!games[currGame].table->isMoveWithStonePossible(currStone))
    {
      Table::Stone nxtStone = (currStone == Table::Stone::BLACK) ? Table::Stone::WHITE : Table::Stone::BLACK;
      if (!games[currGame].table->isMoveWithStonePossible(nxtStone))
      {
        std::string winner = (games[currGame].table->getWhiteStonesCount() > games[currGame].table->getBlackStonesCount()) ?
                             players[1] : players[0];
        std::cout << "================================================================\n";
        std::cout << "                    " << winner;
        std::cout << " WINS!" << std::endl;
        std::cout << ">>";
        char c;
        if (std::cin >> c)
        {
          try
          {
            startNewGameCli();
          }
          catch (const OthelloError &e)
          {
            std::cout << e.what() << std::endl;
            return;
          }
          continue;
        }
      }
      else
      {
        std::cout << "There's no possible move for player ";
        std::cout << players[games[currGame].table->getMoveCount() & 1] << std::endl;
        std::cout << "Passing this turn" << std::endl;
        putStoneIfPossible({0, 0}, Table::Stone::FREE);
        continue;
      }
    }

    if (games[currGame].table->getMoveCount() & 1)
    {
      if (games[currGame].againstAI)
      {
        Table::Coords coords = games[currGame].PC.nextMove(games[currGame].table, Table::Stone::WHITE);
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
      undoMove();
      games[currGame].table->print();
      std::cout << std::endl;
    }
    else if (input == "r" || input == "redo")
    {
      redoMove();
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
    else if (input == "X" || input == "exit")
    {
      closeCurrentGame();
      if (games.empty())
      {
        std::cout << "Good bye!" << std::endl;
        return;
      }
      std::cout << "\tClosing game " << currGame + 2 << std::endl << std::endl;
    }
    else if (input == "new")
    {
      std::cout << "Starting new game...\n" << std::endl;
      try
      {
        startNewGameCli();
      }
      catch (const OthelloError &e)
      {
        std::cout << e.what() << std::endl;
        return;
      }
    }
    else if (input == "next")
    {
      std::cout << "Starting next game. Opened games: " << games.size() + 1 << std::endl;
      try
      {
        startNextGameCli();

      }
      catch (const OthelloError &e)
      {
        std::cout << e.what() << std::endl;
        if (getOpenedGamesCount() == 0)
        {
          return;
        }
      }
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
      switchToGame(index);
    }
    else if (input.size() > 1 && isalpha(input[0]) && isdigit(input[1]))
    {
      char c = input[0];
      int row = input[1] - '0';
      int col;
      row--;
      col = static_cast<int>(c) - static_cast<int>('a');

      Table::Coords coords = std::make_pair(row, col);

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
 * @brief Asks user about parameters for new game and replaces current game with new one.
 */
void OthelloCli::startNewGameCli()
{
  std::cout << "====================================================================" << std::endl;
  std::cout << "                       Welcome to the Othello." << std::endl;
  std::cout << "====================================================================" << std::endl;
  printHelpCli();

  unsigned size = getInitSizeCli();
  bool againstAI = chooseOpponentAICli();
  AIPlayer PC;
  if (againstAI)
  {
    PC.setStrategy(chooseAIOpponentCli());
  }

  startNewGame(size, againstAI, PC);
}

/**
 * @brief Asks user about parameters for next new game and start next new game.
 */
void OthelloCli::startNextGameCli()
{
  std::cout << "====================================================================" << std::endl;
  std::cout << "                       Welcome to the Othello." << std::endl;
  std::cout << "====================================================================" << std::endl;
  printHelpCli();

  unsigned size = getInitSizeCli();
  bool againstAI = chooseOpponentAICli();
  AIPlayer PC;
  if (againstAI)
  {
    PC.setStrategy(chooseAIOpponentCli());
  }

  startNextGame(size, againstAI, PC);
}

void OthelloCli::printHelpCli() const
{
  std::cout << "Game controls:" << std::endl;
  std::cout << "\t H | help --> print this help message" << std::endl;
  std::cout << "\t X | exit --> exit game" << std::endl;
  std::cout << "\t r | redo --> redo one step forward" << std::endl;
  std::cout << "\t u | undo --> undo one step backward" << std::endl;
  std::cout << "\t s | save --> save current game" << std::endl;
  std::cout << "\t load     --> load saved game" << std::endl;
  std::cout << "\t reset    --> resets current game to start state" << std::endl;
  std::cout << "\t new      --> start new game" << std::endl;
  std::cout << "\t next     --> start next game" << std::endl;
  std::cout << "\t AN       --> A is letter for column and N is number of row" << std::endl;
  std::cout << std::endl;
}

/**
 * @brief Asks user whether wants to play against pc
 *
 * @return True if wants to play against PC, @c false otherwise.
 */
bool OthelloCli::chooseOpponentAICli() const
{
  std::cout << "Do you wanna play against computer? (y/n)" << std::endl;
  std::cout << ">>";
  std::string answer;
  std::cin >> answer;
  if (answer == "X" || answer == "exit")
  {
      throw OthelloError("Unexpected end.");
  }

  return tolower(answer[0]) == 'y';
}

/**
 * @brief Asks user for table size.
 */
unsigned OthelloCli::getInitSizeCli() const
{
  unsigned size;
  std::string input;
  while(true)
  {
    std::cout << "Enter size of board - 6, 8, 10 or 12!" << std::endl;
    std::cout << ">>";
    std::cin >> input;

    if (input == "X" || input == "exit")
    {
      throw OthelloError("Unexpected end.");
    }

    if (isdigit(input[0]))
    {
      size = std::stoi(input);
      if (size == 6 || size == 8 || size == 10 || size == 12)
      {
        break;
      }
    }
    std::cout << "Wrong size! 6, 8, 10 or 12" << std::endl;
  }
  return size;
}

/**
 * @brief Asks user for PC algorithm type.
 */
AIPlayer::AIPlayerType OthelloCli::chooseAIOpponentCli() const
{
  while (true)
  {
    std::cout << "Choose your opponent: Monkey(1), Chimpanzee(2)" << std::endl;
    std::cout << ">>";
    std::string res;

    std::cin >> res;
    if (res == "1" || res == "Monkey")
    {
      return AIPlayer::AIPlayerType::Monkey;
    }
    else if (res == "2" || res == "Chimpanzee")
    {
      return AIPlayer::AIPlayerType::Chimpanzee;
    }
    else
    {
      std::cout << "Sorry man, I don't have a " << res << std::endl;
    }
  }
}

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

#include <fstream>
#include <iostream>
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
Othello::Othello() : currGame{0} {}

/**
 * @brief Destructs Othello object.
 */
Othello::~Othello() = default;

/**
 * @brief Starts new game, closes currently opened game.
 */
void Othello::startNewGame(unsigned size, bool againstAI, AIPlayer PC)
{
  auto table = std::make_shared<Table>(size, size);
  if (games.size() > 0)
  {
    games[currGame] = Game(table, againstAI, PC);
  }
  else
  {
    games.emplace_back(table, againstAI, PC);
  }
}

/**
 * @brief Starts next new game alongside currently opened games.
 */
void Othello::startNextGame(unsigned size, bool againstAI, AIPlayer PC)
{
  auto table = std::make_shared<Table>(size, size);
  games.emplace_back(table, againstAI, PC);
  currGame = games.size() - 1;
}

/**
 * @brief Ends current game and previous one becomes active.
 */
void Othello::closeCurrentGame()
{
  if (getOpenedGamesCount() == 0)
  {
    return;
  }

  games.erase(games.begin() + currGame);
  if (currGame > 0)
  {
    currGame--;
  }
}

/**
 * @brief Resets current game to its initial state.
 */
void Othello::resetCurrentGame()
{
  if (getOpenedGamesCount() == 0)
  {
    return;
  }

  int oldRows = games[currGame].table->getRowCount();
  int oldCols = games[currGame].table->getColCount();
  auto table = std::make_shared<Table>(oldRows, oldCols);

  games[currGame] = Game(table, games[currGame].againstAI, games[currGame].PC);
}

/**
 * @brief Tries to put stone on supplied coordinates.
 *
 * @return Returns @c true if stone was put, @c false otherwise.
 */
bool Othello::putStoneIfPossible(Table::Coords coords, Table::Stone stone)
{
  if (getOpenedGamesCount() == 0)
  {
    return false;
  }

  if (games[currGame].table->canPutStone(coords, stone))
  {
    auto moveCmd = std::make_shared<TableMoveCommand>(games[currGame].table, coords, stone);
    games[currGame].cmdManager.executeCmd(moveCmd);
    return true;
  }
  return false;
}


/**
 * @brief Performs undo on current game. If playing against PC, then undo 2 moves.
 */
void Othello::undoMove()
{
  if (getOpenedGamesCount() == 0)
  {
    return;
  }

  games[currGame].cmdManager.undo();

  if (games[currGame].againstAI)
  {
    games[currGame].cmdManager.undo();
  }
}

/**
 * @brief Performs redo on current game. If playing against PC, then redo 2 moves.
 */
void Othello::redoMove()
{
  if (getOpenedGamesCount() == 0)
  {
    return;
  }

  games[currGame].cmdManager.redo();

  if (games[currGame].againstAI)
  {
    games[currGame].cmdManager.redo();
  }
}

/**
 * @brief Loads table status from file and sets it on current table.
 *
 * @return True on successful load, @c false otherwise.
 */
bool Othello::loadGame(const std::string &fileName)
{
  if (getOpenedGamesCount() == 0)
  {
    startNewGame(Table::DEFAULT_ROWS, false);
    currGame = 0;
  }

  Table::Board board;
  bool againstAI;
  AIPlayer::AIPlayerType playerType;

  std::ifstream ifs(fileName);
  try
  {
    boost::archive::text_iarchive ia(ifs);
    ia >> board >> againstAI >> playerType;
  }
  catch(boost::archive::archive_exception)
  {
    return false;
  }

  games[currGame].table->setBoard(board);
  games[currGame].againstAI = againstAI;
  games[currGame].PC.setStrategy(playerType);
  return true;
}

/**
 * @brief Saves current table status to file.
 *
 * @return True on successful save, @c false otherwise.
 */
bool Othello::saveGame(const std::string &fileName) const
{
  if (getOpenedGamesCount() == 0)
  {
    return true;
  }

  Table::Board board = games[currGame].table->getBoard();
  bool againstAI = games[currGame].againstAI;
  AIPlayer::AIPlayerType playerType = games[currGame].PC.getPlayerType();

  std::ofstream ofs(fileName);

  try
  {
    boost::archive::text_oarchive oa(ofs);
    oa << board << againstAI << playerType;
  }
  catch(boost::archive::archive_exception)
  {
    return false;
  }

  return true;
}

/**
 * @brief Returns count of all currently opened games.
 */
unsigned Othello::getOpenedGamesCount() const
{
  return games.size();
}

/**
 * @brief Switches current game.
 *
 * @par Preconditions
 *  - <tt>0 < index <= count_of_opened_games </tt>
 */
void Othello::switchToGame(unsigned index)
{
  if (index <= getOpenedGamesCount() && index > 0)
  {
    currGame = index - 1;
  }
}

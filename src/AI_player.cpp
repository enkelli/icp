/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief Implementation of command manager.
 * @file AI_player.cpp
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include "AI_player.h"
#include "algorithm.h"
#include "algorithm_monkey.h"
#include "algorithm_chimpanzee.h"

/**
 * @brief Creates new PC player.
 */
AIPlayer::AIPlayer(AIPlayerType playerType)
{
  setStrategy(playerType);
}

/**
 * @brief Copy constructor.
 */
AIPlayer::AIPlayer(const AIPlayer &player)
{
  setStrategy(player.playerType);
}

/**
 * @brief Sets new algorithm for PC player.
 *
 * @param playerType Should by one of @c enum @c AIPlayerType.
 */
void AIPlayer::setStrategy(AIPlayerType newType)
{
  switch(newType)
  {
    case (AIPlayerType::Monkey):
      playerType = AIPlayerType::Monkey;
      algorithm = std::make_shared<AlgorithmMonkey>();
      break;
    case (AIPlayerType::Chimpanzee):
      playerType = AIPlayerType::Chimpanzee;
      algorithm = std::make_shared<AlgorithmChimpanzee>();
      break;
    default:
      playerType = AIPlayerType::Monkey;
      algorithm = std::make_shared<AlgorithmMonkey>();
  }
}

/**
 * @brief Returns current type of algorithm used by PC player.
 */
AIPlayer::AIPlayerType AIPlayer::getPlayerType() const
{
  return playerType;
}

/**
 * @brief Returns coordinates of next PC's move.
 */
Table::Coords AIPlayer::nextMove(const std::shared_ptr<Table> &table, Table::Stone stone) const
{
  return algorithm->nextMove(table, stone);
}

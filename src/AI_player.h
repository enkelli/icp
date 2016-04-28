/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief Strategy design pattern to choose PC algorithm.
 * @file AI_player.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include <memory>

#include "table.h"

class Algorithm;

/**
 * @brief A representation of PC player.
 */
class AIPlayer
{
  public:
    /// Types of algorithms that PC knows.
    enum class AIPlayerType
    {
      Monkey,
      Chimpanzee,
    };

  public:
    AIPlayer(AIPlayerType playerType = AIPlayerType::Monkey);
    AIPlayer(const AIPlayer &player);

    void setStrategy(AIPlayerType playerType);
    AIPlayerType getPlayerType() const;
    Table::Coords nextMove(const std::shared_ptr<Table> &table, Table::Stone stone) const;

  private:
    /// Type of algorithm.
    AIPlayerType playerType;
    /// Concrete algorithm used by PC.
    std::shared_ptr<Algorithm> algorithm;
};

#endif

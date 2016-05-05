/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief A representation of Othello brain.
 * @file othello.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#ifndef OTHELLO_H
#define OTHELLO_H

#include <string>
#include <vector>

#include "AI_player.h"
#include "game.h"
#include "table.h"

/**
 * @brief A representation of Othello brain.
 */
class Othello
{
  public:
    Othello();
    virtual ~Othello();

  public:
    /// @name Games handling
    /// @{
    void startNewGame(unsigned size, bool againstAI, AIPlayer PC = AIPlayer());
    void startNextGame(unsigned size, bool againstAI, AIPlayer PC = AIPlayer());
    void closeCurrentGame();
    void resetCurrentGame();
    bool loadGame(const std::string &fileName);
    bool saveGame(const std::string &fileName) const;
    void switchToGame(unsigned index);
    /// @}

    /// @name Gameplay controls
    /// @{
    Table::Stone getCurrentMoveStone() const;
    Table::Stone getNextMoveStone() const;
    bool putStoneIfPossible(Table::Coords coords, Table::Stone stone);
    void undoMove();
    void redoMove();
    /// @}

  protected:
    unsigned getOpenedGamesCount() const;

  protected:
    /// Index of active game.
    unsigned currGame;

    using Games = std::vector<Game>;
    /// Storage for all opened games.
    Games games;
};

#endif

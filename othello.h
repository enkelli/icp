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

#include "game.h"

/**
 * @brief A representation of Othello brain.
 */
class Othello
{
  public:
    Othello();

    void play();

  private:
    void startNewGame();
    void closeCurrentGame();
    void printCliHelp() const;
    unsigned getInitSize() const;
    bool chooseOpponentAI() const;
    void saveCurrentGame() const;

  private:
    /// Index of active game.
    unsigned currGame;

    using Games = std::vector<Game>;
    /// Storage for all opened games.
    Games games;
};

#endif

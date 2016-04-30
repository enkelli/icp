/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief A representation of Othello command line interface.
 * @file othello_cli.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#ifndef OTHELLO_CLI_H
#define OTHELLO_CLI_H

#include "othello.h"

/**
 * @brief A representation of Othello command line interface.
 */
class OthelloCli: public Othello
{
  public:
    OthelloCli();

    void playCli();

  private:
    /// @name CLI interface
    /// @{
    void startNewGameCli();
    void startNextGameCli();
    void printHelpCli() const;
    unsigned getInitSizeCli() const;
    bool chooseOpponentAICli() const;
    AIPlayer::AIPlayerType chooseAIOpponentCli() const;
    /// @}
};

#endif

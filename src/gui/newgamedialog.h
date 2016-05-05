/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief A representation of Othello table.
 * @file newgamedialog.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>

namespace Ui {
class NewGameDialog;
}

class NewGameDialog : public QDialog
{
    Q_OBJECT

public:
    enum class Algo
    {
        MONKEY,
        CHIMPANZEE,
        PLAYER
    };

public:
    explicit NewGameDialog(QWidget *parent = 0);
    ~NewGameDialog();

public:
    int getTableSize();
    Algo getAlgo();

private:
    Ui::NewGameDialog *ui;
};

#endif // NEWGAMEDIALOG_H

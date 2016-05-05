/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief A representation of Othello table.
 * @file newgamedialog.cpp
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include "newgamedialog.h"
#include "ui_newgamedialog.h"

NewGameDialog::NewGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGameDialog)
{
    ui->setupUi(this);
}

NewGameDialog::~NewGameDialog()
{
    delete ui;
}

int NewGameDialog::getTableSize()
{
    switch(ui->sizeSelect->currentIndex())
    {
    case 0:
        return 6;
    case 1:
        return 8;
    case 2:
        return 10;
    case 3:
        return 12;
    default:
        return 8;
    }
}

NewGameDialog::Algo NewGameDialog::getAlgo()
{
    switch(ui->opponentSelect->currentIndex())
    {
    case 0:
        return Algo::MONKEY;
    case 1:
        return Algo::CHIMPANZEE;
    default:
        return Algo::PLAYER;
    }
}

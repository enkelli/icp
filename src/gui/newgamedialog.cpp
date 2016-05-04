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

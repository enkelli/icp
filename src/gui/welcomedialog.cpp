#include "welcomedialog.h"
#include "ui_welcomedialog.h"

WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeDialog)
{
    ui->setupUi(this);
}

WelcomeDialog::~WelcomeDialog()
{
    delete ui;
}

int WelcomeDialog::getTableSize()
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

WelcomeDialog::Algo WelcomeDialog::getAlgo()
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

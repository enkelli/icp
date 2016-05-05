/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief A representation of Othello table.
 * @file welcomedialog.cpp
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include "welcomedialog.h"
#include "ui_welcomedialog.h"

WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    connect(this, SIGNAL(newGameClick()), parentWidget(), SLOT(on_actionNew_Game_triggered()));
    connect(this, SIGNAL(loadGameClick()), parentWidget(), SLOT(on_actionLoad_triggered()));
    connect(this, SIGNAL(exitClick()), parentWidget(), SLOT(slotImmediateExit()));
}

WelcomeDialog::~WelcomeDialog()
{
    delete ui;
}

void WelcomeDialog::on_newButton_clicked()
{
    emit newGameClick();
    close();
}

void WelcomeDialog::on_loadButton_clicked()
{
    emit loadGameClick();
    close();
}

void WelcomeDialog::on_exitButton_clicked()
{
    emit exitClick();
    close();
}

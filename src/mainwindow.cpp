/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief GUI main window file.
 * @file mainwindow.cpp
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap blackStone(":img/black.png");
    QPixmap whiteStone(":img/white.png");

    ui->gridLayout->setSpacing(0);

    for(int i=0; i<64; i++)
    {
    QLabel *l1 = new QLabel(this);
    l1->setAlignment(Qt::AlignCenter);

    const char *css = "border-style: solid; border-width: 0 1px 1px 0";

    if(i == 63)
        css = "border-style: none;";
    else if(i % 8 == 7 && i < 56)
        css = "border-style: solid; border-width: 0 0 1px 0";
    else if(i >= 56)
        css = "border-style: solid; border-width: 0 1px 0 0";

    l1->setStyleSheet(css);

    (i&1) ? l1->setPixmap(blackStone) : l1->setPixmap(whiteStone);

    ui->gridLayout->addWidget(l1, i>>3, i&7);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

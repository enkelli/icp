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

#include <memory>

#include <QDir>
#include <QFileDialog>
#include <QPixmap>
#include <QString>
#include <QtConcurrent/QtConcurrent>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stonewidget.h"

#include "exception.h"
#include "table.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gridLayout->setSpacing(0);

    pixmapBlack = QPixmap(":img/black.png");
    pixmapWhite = QPixmap(":img/white.png");

    aiLock = false;

    startNewGame(12, true);

    initializeGrid();
}

void MainWindow::cleanGrid()
{
    for(StoneWidget* p : pieces)
        delete p;

    pieces.clear();
}

void MainWindow::initializeGrid()
{
    cleanGrid();

    const Table::Board board = games[currGame].table->getBoard();

    int rows = games[currGame].table->getRowCount();
    int cols = games[currGame].table->getColCount();

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            int index = games[currGame].table->getVecIndex(std::make_pair(i, j));
            const Table::Stone stone = board.tableMatrix[index];

            StoneWidget *stoneWidget = new StoneWidget(i, j, this);
            pieces.push_back(stoneWidget);

            stoneWidget->setAlignment(Qt::AlignCenter);

            const char *css = "border-style: solid; border-width: 0 1px 1px 0";

            // Last column, last row
            if(i == rows - 1 && j == cols - 1)
                css = "border-style: none;";
            // Last column not in the last row
            else if(j == cols - 1)
                css = "border-style: solid; border-width: 0 0 1px 0";
            // Last row
            else if(i == rows - 1)
                css = "border-style: solid; border-width: 0 1px 0 0";

            stoneWidget->setStyleSheet(css);

            if(stone == Table::Stone::BLACK)
                stoneWidget->setPixmap(pixmapBlack);
            else if(stone == Table::Stone::WHITE)
                stoneWidget->setPixmap(pixmapWhite);

            ui->gridLayout->addWidget(stoneWidget, i, j);
        }
    }
}

void MainWindow::redrawGrid()
{

    const Table::Board board = games[currGame].table->getBoard();

    int rows = games[currGame].table->getRowCount();
    int cols = games[currGame].table->getColCount();

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            int index = games[currGame].table->getVecIndex(std::make_pair(i, j));
            const Table::Stone stone = board.tableMatrix[index];

            StoneWidget *stoneWidget = pieces[i*cols + j];

            if(stone == Table::Stone::BLACK)
            {
                stoneWidget->setPixmap(pixmapBlack);
            }
            else if(stone == Table::Stone::WHITE)
            {
                stoneWidget->setPixmap(pixmapWhite);
            }
            else
            {
                stoneWidget->clear();
            }
        }
    }

    updateScore();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString getPathToExamples()
{
    return QDir::cleanPath(qApp->applicationDirPath() + QDir::separator() + "examples");
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save game"), getPathToExamples());
    saveGame(fileName.toStdString());
}

void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load game"), getPathToExamples());
    loadGame(fileName.toStdString());
    redrawGrid();
}

void MainWindow::on_actionExit_triggered()
{
    cleanGrid();
    qApp->exit();
}

void MainWindow::aiMove(StoneWidget *w)
{
    aiLock = true;
    auto stone = Table::Stone::WHITE;
    Table::Coords nc;

    try
    {
      nc = games[currGame].PC.nextMove(games[currGame].table, Table::Stone::WHITE);
    }
    catch (const OthelloError &e)
    {
      stone = Table::Stone::FREE;
    }

    putStoneIfPossible(nc, stone);
    redrawGrid();

    // Clear locked widget background
    w->setAutoFillBackground(false);

    aiLock = false;
}

void MainWindow::updateScore()
{
    ui->scoreBlack->display(games[currGame].table->getBlackStonesCount());
    ui->scoreWhite->display(games[currGame].table->getWhiteStonesCount());
}

void MainWindow::slotClicked(StoneWidget *w)
{
    Table::Coords c = std::make_pair(w->getRow(), w->getCol());

    if(games[currGame].table->canPutStone(c, Table::Stone::BLACK) && !aiLock)
    {
        putStoneIfPossible(c, Table::Stone::BLACK);
        redrawGrid();
        QFuture<void> future = QtConcurrent::run(this, &MainWindow::aiMove, w);
    }
}

void MainWindow::slotLeft(StoneWidget *w)
{
    if(!aiLock)
        w->setAutoFillBackground(false);
}

void MainWindow::slotEntered(StoneWidget *w)
{
    if(!aiLock)
    {
        w->setAutoFillBackground(true);
        QPalette palette = w->palette();

        if(games[currGame].table->canPutStone(std::make_pair(w->getRow(), w->getCol()), Table::Stone::BLACK))
            palette.setColor(QPalette::Window, QColor(81, 207, 114, 50));
        else
            palette.setColor(QPalette::Window, QColor(207, 79, 79, 50));

        w->setPalette(palette);
    }
}

void MainWindow::on_actionUndo_triggered()
{
    undoMove();
    redrawGrid();
}

void MainWindow::on_actionRedo_triggered()
{
    redoMove();
    redrawGrid();
}

void MainWindow::on_actionReset_triggered()
{
    resetCurrentGame();
    redrawGrid();
}

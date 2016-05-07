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
#include <QMessageBox>
#include <QPixmap>
#include <QString>
#include <QtConcurrentRun>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stonewidget.h"
#include "newgamedialog.h"
#include "welcomedialog.h"
#include "aboutdialog.h"

#include "exception.h"
#include "table.h"

/**
 * @brief Creates new window.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gridLayout->setSpacing(0);

    pixmapBlack = QPixmap(":img/black.png");
    pixmapWhite = QPixmap(":img/white.png");

    redBg = QColor(207, 79, 79, 50);
    greenBg =  QColor(81, 207, 114, 50);

    playerLock = true;

    show();

    showWelcomeDialog();
}

/**
 * @brief Destructs window.
 */
MainWindow::~MainWindow()
{
    cleanGrid();
    delete ui;
}

/**
 * @brief Cleans stone widgets on heap.
 */
void MainWindow::cleanGrid()
{
    for(StoneWidget* p : pieces)
        delete p;

    pieces.clear();
}

/**
 * @brief Creates new stone widgets.
 */
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

            // First row, first column
            if(i == 0 && j == 0)
                css = "border-style: solid; border-width: 1px 1px 1px 1px";
            // First row
            else if(i == 0)
                css = "border-style: solid; border-width: 1px 1px 1px 0";
            // First column
            else if(j == 0)
                css = "border-style: solid; border-width: 0 1px 1px 1px";

            stoneWidget->setStyleSheet(css);

            if(stone == Table::Stone::BLACK)
                stoneWidget->setPixmap(pixmapBlack);
            else if(stone == Table::Stone::WHITE)
                stoneWidget->setPixmap(pixmapWhite);

            ui->gridLayout->addWidget(stoneWidget, i, j);
        }
    }

    updateOnTurnIndicator();
    updateScore();
}

/**
 * @brief Update grid after new stone was placed etc.
 */
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

    updateOnTurnIndicator();
    updateScore();
}

/**
 * @brief Returns path to folder with saved files.
 */
QString getPathToExamples()
{
    return QDir::cleanPath(qApp->applicationDirPath() + QDir::separator() + "examples");
}

/**
 * @brief Save current game.
 */
void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save game"), getPathToExamples());
    saveGame(fileName.toStdString());
}

/**
 * @brief Load game from file.
 */
void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load game"), getPathToExamples());
    if(loadGame(fileName.toStdString()))
    {
        initializeGrid();
        playerLock = false;
    }
}

/**
 * @brief Close game.
 */
void MainWindow::slotImmediateExit()
{
    QTimer::singleShot(0, this, SLOT(close()));
}

/**
 * @brief Checks if currGame 'pointer' is valid.
 */
bool MainWindow::currentGameValid()
{
    return (currGame < getOpenedGamesCount());
}

/**
 * @brief Calls message box with game over message.
 */
void MainWindow::gameOver()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this, "Othello", "Game over", QMessageBox::Ok);

    if(reply == QMessageBox::Ok)
    {
        //resetCurrentGame();
        //redrawGrid();
    }
}

/**
 * @brief Calls AI algorithm to perform next move.
 */
void MainWindow::aiMove()
{
    playerLock = true;

    auto stone = getCurrentMoveStone();
    Table::Coords nc;

    do
    {
        try
        {
            nc = games[currGame].PC.nextMove(games[currGame].table, stone);
        }
        catch (const OthelloError&)
        {
            stone = Table::Stone::FREE;
        }

        putStoneIfPossible(nc, stone);
    }
    while(!games[currGame].table->isMoveWithStonePossible(Table::Stone::BLACK) && games[currGame].table->isMoveWithStonePossible(Table::Stone::WHITE));

    playerLock = false;
}

/**
 * @brief Updates gui stone for next player.
 */
void MainWindow::updateOnTurnIndicator()
{
    if (getCurrentMoveStone() == Table::Stone::WHITE)
    {
        ui->labelOnTurnStone->setPixmap(pixmapWhite);
    }
    else
    {
        ui->labelOnTurnStone->setPixmap(pixmapBlack);
    }
}

/**
 * @brief Updates gui scoreboard.
 */
void MainWindow::updateScore()
{
    ui->scoreBlack->display(games[currGame].table->getBlackStonesCount());
    ui->scoreWhite->display(games[currGame].table->getWhiteStonesCount());
}

/**
 * @brief Slot for click on square.
 */
void MainWindow::slotClicked(StoneWidget *w)
{
    Table::Coords coords = std::make_pair(w->getRow(), w->getCol());
    Table::Stone stone = getCurrentMoveStone();

    if(putStoneIfPossible(coords, stone) && !playerLock)
    {
        redrawGrid();

        if(games[currGame].againstAI)
        {
            QFuture<void> future = QtConcurrent::run(this, &MainWindow::aiMove);

            // This will wait for AI to finish but not block the current redraw operation
            while(future.isRunning())
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            redrawGrid();
            w->setAutoFillBackground(false);
        }
        else
        {
            // If the next player cannot move, invert the active stone color
            stone = getCurrentMoveStone();
            if(!games[currGame].table->isMoveWithStonePossible(stone))
            {
                putStoneIfPossible({1,2}, Table::Stone::FREE);
                updateOnTurnIndicator();
            }
        }

        // No more moves are possible -> game over
        if(!games[currGame].table->isMoveWithStonePossible(Table::Stone::BLACK) && !games[currGame].table->isMoveWithStonePossible(Table::Stone::WHITE))
            gameOver();
    }
}

/**
 * @brief Mouse moved out of square.
 */
void MainWindow::slotLeft(StoneWidget *w)
{
    if(!playerLock)
        w->setAutoFillBackground(false);
}

/**
 * @brief Mouse moved inside square.
 */
void MainWindow::slotEntered(StoneWidget *w)
{
    if(!playerLock)
    {
        w->setAutoFillBackground(true);
        QPalette palette = w->palette();

        if(games[currGame].table->canPutStone(std::make_pair(w->getRow(), w->getCol()), getCurrentMoveStone()))
            palette.setColor(QPalette::Window, greenBg);
        else
            palette.setColor(QPalette::Window, redBg);

        w->setPalette(palette);
    }
}

/**
 * @brief Dialog for new game.
 */
void MainWindow::showNewGameDialog()
{
    NewGameDialog w(this);

    if(w.exec() == QDialog::Accepted)
    {
        int tableSize = w.getTableSize();
        NewGameDialog::Algo algo = w.getAlgo();

        switch(algo)
        {
        case NewGameDialog::Algo::CHIMPANZEE:
            startNewGame(tableSize, true, AIPlayer(AIPlayer::AIPlayerType::Chimpanzee));
            break;
        case NewGameDialog::Algo::MONKEY:
            startNewGame(tableSize, true, AIPlayer(AIPlayer::AIPlayerType::Monkey));
            break;
        default:
            startNewGame(tableSize, false);
        }

        initializeGrid();

        playerLock = false;

        return;
    }
}

/**
 * @brief Dialog shown at the beginning.
 */
void MainWindow::showWelcomeDialog()
{
    WelcomeDialog w(this);
    w.exec();
}

/**
 * @brief Perform undo action.
 */
void MainWindow::on_actionUndo_triggered()
{
    if(currentGameValid())
    {
        undoMove();
        redrawGrid();
    }
}

/**
 * @brief Perform redo action.
 */
void MainWindow::on_actionRedo_triggered()
{
    if(currentGameValid())
    {
        redoMove();
        redrawGrid();
        // No more moves are possible -> game over
        if(!games[currGame].table->isMoveWithStonePossible(Table::Stone::BLACK) && !games[currGame].table->isMoveWithStonePossible(Table::Stone::WHITE))
            gameOver();
    }
}

/**
 * @brief Reset current game to initial state.
 */
void MainWindow::on_actionReset_triggered()
{
    if(currentGameValid())
    {
        resetCurrentGame();
        redrawGrid();
    }
}

/**
 * @brief Start new game.
 */
void MainWindow::on_actionNew_Game_triggered()
{
    showNewGameDialog();
}

/**
 * @brief Call exit.
 */
void MainWindow::on_actionExit_triggered()
{
    this->close();
}

/**
 * @brief Override close function to ask user whether he really wants to exit.
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Othello", "Quit game?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

/**
 * @brief Show 'about this program' dialog.
 */
void MainWindow::on_actionAbout_triggered()
{
    AboutDialog d(this);
    d.exec();
}

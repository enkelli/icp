/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief GUI main window file.
 * @file mainwindow.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <vector>

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QLabel>
#include <QColor>

#include "stonewidget.h"

#include "table.h"
#include "othello.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, Othello
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void drawTable();

private:
    void cleanGrid();
    void initializeGrid();
    void redrawGrid();
    void aiMove();
    void updateOnTurnIndicator();
    void updateScore();
    void showNewGameDialog();
    bool currentGameValid();
    Table::Stone getCurrentStone();
    void showWelcomeDialog();

public slots:
    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_actionExit_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionReset_triggered();

    void on_actionNew_Game_triggered();

public slots:
    void slotClicked(StoneWidget *w);
    void slotEntered(StoneWidget *w);
    void slotLeft(StoneWidget *w);
    void slotImmediateExit();

private:
    QColor redBg;
    QColor greenBg;

    Ui::MainWindow *ui;

    std::vector<StoneWidget*> pieces;
    QPixmap pixmapBlack;
    QPixmap pixmapWhite;

    Table::Stone firstPlayerStone = Table::Stone::BLACK;
    bool playerLock;
};

#endif // MAINWINDOW_H

/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief GUI main window file.
 * @file stonewidget.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#ifndef STONEWIDGET_H
#define STONEWIDGET_H

#include <QLabel>
#include <QtCore>
#include <QtGui>
#include <QWidget>

class StoneWidget : public QLabel
{
    Q_OBJECT

public:
    StoneWidget(int, int, QWidget*);
    StoneWidget(QWidget*);
    ~StoneWidget();

public:
    int getRow();
    int getCol();

private:
    int row;
    int col;

signals:
    void clicked(StoneWidget *w);
    void entered(StoneWidget *w);
    void left(StoneWidget *w);

private:
    void mousePressEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
};

#endif // STONEWIDGET_H

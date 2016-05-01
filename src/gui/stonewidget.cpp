/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief GUI main window file.
 * @file stonewidget.cpp
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include <QtGui>
#include <QWidget>
#include <QLabel>

#include "stonewidget.h"

StoneWidget::StoneWidget(int r, int c, QWidget *parent) : QLabel(parent), row{r}, col{c}
{
    connect(this, SIGNAL(clicked(StoneWidget*)), parentWidget(), SLOT(slotClicked(StoneWidget*)));
    connect(this, SIGNAL(entered(StoneWidget*)), parentWidget(), SLOT(slotEntered(StoneWidget*)));
    connect(this, SIGNAL(left(StoneWidget*)), parentWidget(), SLOT(slotLeft(StoneWidget*)));
}

StoneWidget::StoneWidget(QWidget *parent)
{
    StoneWidget(0, 0, parent);
}

StoneWidget::~StoneWidget() {}

void StoneWidget::mousePressEvent(QMouseEvent * event)
{
    emit clicked(this);
}

void StoneWidget::leaveEvent(QEvent *event)
{
    emit left(this);
}

void StoneWidget::enterEvent(QEvent *event)
{
    emit entered(this);
}

int StoneWidget::getCol()
{
    return col;
}

int StoneWidget::getRow()
{
    return row;
}

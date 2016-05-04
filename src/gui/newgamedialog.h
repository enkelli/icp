#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>

namespace Ui {
class NewGameDialog;
}

class NewGameDialog : public QDialog
{
    Q_OBJECT

public:
    enum class Algo
    {
        MONKEY,
        CHIMPANZEE,
        PLAYER
    };

public:
    explicit NewGameDialog(QWidget *parent = 0);
    ~NewGameDialog();

public:
    int getTableSize();
    Algo getAlgo();

private:
    Ui::NewGameDialog *ui;
};

#endif // NEWGAMEDIALOG_H

#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>

namespace Ui {
class WelcomeDialog;
}

class WelcomeDialog : public QDialog
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
    explicit WelcomeDialog(QWidget *parent = 0);
    ~WelcomeDialog();

public:
    int getTableSize();
    Algo getAlgo();

private:
    Ui::WelcomeDialog *ui;
};

#endif // WELCOMEDIALOG_H

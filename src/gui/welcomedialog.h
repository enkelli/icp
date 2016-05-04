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
    explicit WelcomeDialog(QWidget *parent = 0);
    ~WelcomeDialog();

private slots:
    void on_newButton_clicked();

    void on_loadButton_clicked();

    void on_exitButton_clicked();

signals:
    void newGameClick();
    void loadGameClick();
    void exitClick();

private:
    Ui::WelcomeDialog *ui;
};

#endif // WELCOMEDIALOG_H

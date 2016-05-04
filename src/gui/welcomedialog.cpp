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

#include "account_dialog.h"
#include "ui_account_dialog.h"

account_dialog::account_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::account_dialog)
{
    ui->setupUi(this);
}

account_dialog::~account_dialog()
{
    delete ui;
}

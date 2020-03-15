#include "expense_dialog.h"
#include "ui_expense_dialog.h"

expense_dialog::expense_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::expense_dialog)
{
    ui->setupUi(this);
}

expense_dialog::~expense_dialog()
{
    delete ui;
}

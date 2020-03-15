#include "department_dialog.h"
#include "ui_department_dialog.h"

department_dialog::department_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::department_dialog)
{
    ui->setupUi(this);
}

department_dialog::~department_dialog()
{
    delete ui;
}

#include "department_widget.h"
#include "ui_department_widget.h"

DepartmentWidget::DepartmentWidget(WidgetPurpose widget_purpose, int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DepartmentWidget)
{
    ui->setupUi(this);
    switch (widget_purpose)
    {
        case ADD:
            ui->pushButton->setText("Add");
            break;
        case EDIT:
        {
            auto department = ControlUnit::getInstance()->getDepartment(id);
            ui->pushButton->setText("Save");
            ui->idEdit->setText(QString::number(id));
            ui->titleEdit->setText(std::get<0>(department));
            ui->membersCountEdit->setText(QString::number(std::get<1>(department)));
            break;
        }
    }
}

DepartmentWidget::~DepartmentWidget()
{
    delete ui;
}

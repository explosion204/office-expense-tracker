#include "department_widget.h"
#include "ui_department_widget.h"

DepartmentWidget::DepartmentWidget(WidgetPurpose widget_purpose, Department *department, QWidget *parent) :
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
            ui->pushButton->setText("Save");
            break;
        default:
            break;
    }
    this->department = department;
}

DepartmentWidget::~DepartmentWidget()
{
    delete ui;
}

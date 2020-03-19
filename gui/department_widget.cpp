#include "department_widget.h"
#include "ui_department_widget.h"

DepartmentWidget::DepartmentWidget(WidgetPurpose widget_purpose, int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DepartmentWidget)
{
    ui->setupUi(this);
    this->purpose = widget_purpose;
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

void DepartmentWidget::on_pushButton_clicked()
{
    QString id = ui->idEdit->text();
    QString title = ui->titleEdit->text();
    QString members_count = ui->membersCountEdit->text();
    if (!id.isEmpty() && !title.isEmpty() && !members_count.isEmpty())
    {
        switch (purpose)
        {
            case ADD:
                ControlUnit::getInstance()->addDepartment(id.toInt(), title, members_count.toInt());
                break;
            case EDIT:
                ControlUnit::getInstance()->editDepartment(id.toInt(), title, members_count.toInt());
                break;
        }
        updateListWidget();
    }
}


void DepartmentWidget::on_cancelButton_clicked()
{

}

#ifndef DEPARTMENT_WIDGET_H
#define DEPARTMENT_WIDGET_H

#include <QWidget>
#include <data/department.h>
#include <gui/widget_purpose.h>

namespace Ui {
class DepartmentWidget;
}

class DepartmentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DepartmentWidget(WidgetPurpose widget_purpose, Department *department, QWidget *parent = nullptr);
    ~DepartmentWidget();

private:
    Ui::DepartmentWidget *ui;
    Department *department;
};

#endif // DEPARTMENT_WIDGET_H

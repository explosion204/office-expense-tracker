#ifndef DEPARTMENT_WIDGET_H
#define DEPARTMENT_WIDGET_H

#include <QWidget>
#include <service/controlunit.h>
#include <gui/widget_purpose.h>

namespace Ui {
class DepartmentWidget;
}

class DepartmentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DepartmentWidget(WidgetPurpose widget_purpose, int id, QWidget *parent = nullptr);
    ~DepartmentWidget();

signals:
    void updateListWidget();
    void cancel();

private slots:
    void on_pushButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::DepartmentWidget *ui;
    WidgetPurpose purpose;
};

#endif // DEPARTMENT_WIDGET_H

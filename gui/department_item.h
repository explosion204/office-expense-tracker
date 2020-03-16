#ifndef DEPARTMENT_WIDGET_ITEM_H
#define DEPARTMENT_WIDGET_ITEM_H

#include <QListWidgetItem>
#include <QString>

class DepartmentItem : public QListWidgetItem
{
private:
    int id;
public:
    DepartmentItem(int id, QString string_repr);
    int getId();
};

#endif // DEPARTMENT_WIDGET_ITEM_H

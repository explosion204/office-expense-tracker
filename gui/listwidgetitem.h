#ifndef LISTWIDGETITEM_H
#define LISTWIDGETITEM_H

#include <QListWidgetItem>
#include <QString>

class ListWidgetItem : public QListWidgetItem
{
private:
    int item_id;
public:
    ListWidgetItem(int item_id, QString string_repr);
    int getItemId();
};

#endif // LISTWIDGETITEM_H

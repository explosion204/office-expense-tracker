#include "listwidgetitem.h"

ListWidgetItem::ListWidgetItem(int item_id, QString string_repr) : QListWidgetItem(string_repr)
{
    this->item_id = item_id;
}

int ListWidgetItem::getItemId() { return item_id; }

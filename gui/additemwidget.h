#ifndef ADDITEMWIDGET_H
#define ADDITEMWIDGET_H

#include <QWidget>

namespace Ui {
class AddItemWidget;
}

class AddItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddItemWidget(QWidget *parent = nullptr);
    ~AddItemWidget();

private:
    Ui::AddItemWidget *ui;
};

#endif // ADDITEMWIDGET_H

#ifndef ADDWIDGET_H
#define ADDWIDGET_H

#include <QWidget>

namespace Ui {
class AddWidget;
}

class AddWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddWidget(QWidget *parent = nullptr);
    ~AddWidget();

private:
    Ui::AddWidget *ui;
};

#endif // ADDWIDGET_H

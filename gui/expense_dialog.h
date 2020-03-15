#ifndef EXPENSE_DIALOG_H
#define EXPENSE_DIALOG_H

#include <QDialog>

namespace Ui {
class expense_dialog;
}

class expense_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit expense_dialog(QWidget *parent = nullptr);
    ~expense_dialog();

private:
    Ui::expense_dialog *ui;
};

#endif // EXPENSE_DIALOG_H

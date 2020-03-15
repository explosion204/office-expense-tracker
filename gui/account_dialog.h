#ifndef ACCOUNT_DIALOG_H
#define ACCOUNT_DIALOG_H

#include <QDialog>

namespace Ui {
class account_dialog;
}

class account_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit account_dialog(QWidget *parent = nullptr);
    ~account_dialog();

private:
    Ui::account_dialog *ui;
};

#endif // ACCOUNT_DIALOG_H

#ifndef DEPARTMENT_DIALOG_H
#define DEPARTMENT_DIALOG_H

#include <QDialog>

namespace Ui {
class department_dialog;
}

class department_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit department_dialog(QWidget *parent = nullptr);
    ~department_dialog();

private:
    Ui::department_dialog *ui;
};

#endif // DEPARTMENT_DIALOG_H

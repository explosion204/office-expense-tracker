#include "additemwidget.h"
#include "ui_additemwidget.h"

AddItemWidget::AddItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddItemWidget)
{
    ui->setupUi(this);
}

AddItemWidget::~AddItemWidget()
{
    delete ui;
}

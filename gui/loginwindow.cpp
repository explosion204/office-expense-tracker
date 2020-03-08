#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <QSslSocket>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    Animation::fadeOut(ui->masterKeyEdit, 0);
    Animation::fadeOut(ui->usernameEdit, 0);
    Animation::fadeOut(ui->passwordEdit, 0);
    Animation::fadeOut(ui->loginButton, 0);
    Animation::fadeOut(ui->createButton, 0);
    ui->loginButton->hide();
    ui->createButton->hide();
    db_path = QString();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    ControlUnit::getInstance()->authorize(db_path, ui->masterKeyEdit->text(), ui->usernameEdit->text(), ui->passwordEdit->text());
    if (ControlUnit::getInstance()->isAuthorized())
    {
        close();
        (new MainWindow())->show();
    }
}

void LoginWindow::on_createDBButton_clicked()
{
    ui->backButton->setEnabled(true);
    showAuthEdits();
    ui->createButton->show();
    ui->createButton->setEnabled(true);
    Animation::fadeIn(ui->createButton, 350);
}

void LoginWindow::on_openDBButton_clicked()
{
    ui->backButton->setEnabled(true);
    db_path = QFileDialog::getOpenFileName(this, tr("Open a database file"), "", tr("database file (*.db)"));
    if (!db_path.isEmpty())
    {
        showAuthEdits();
        Animation::fadeIn(ui->loginButton, 350);
        ui->loginButton->show();
        ui->loginButton->setEnabled(true);
    }
}

void LoginWindow::on_createButton_clicked()
{
    if (!ui->masterKeyEdit->text().isEmpty() && !ui->usernameEdit->text().isEmpty() && !ui->passwordEdit->text().isEmpty())
    {
        QString db_path = QFileDialog::getSaveFileName(this, tr("Save new database"), "", tr("database files (*.db)"));
        ControlUnit::getInstance()->initDatabase(db_path, ui->masterKeyEdit->text(), ui->usernameEdit->text(), ui->passwordEdit->text());
    }
    showStartup();
}

void LoginWindow::showAuthEdits()
{
    ui->backButton->setEnabled(true);
    Animation::fadeOut(ui->createDBButton, 350);
    Animation::fadeOut(ui->openDBButton, 350);
    Animation::fadeIn(ui->masterKeyEdit, 350);
    Animation::fadeIn(ui->usernameEdit, 350);
    Animation::fadeIn(ui->passwordEdit, 350);
    ui->createDBButton->setEnabled(false);
    ui->openDBButton->setEnabled(false);
    ui->masterKeyEdit->setEnabled(true);
    ui->usernameEdit->setEnabled(true);
    ui->passwordEdit->setEnabled(true);
}

void LoginWindow::showStartup()
{
    ui->backButton->setEnabled(false);
    Animation::fadeIn(ui->createDBButton, 350);
    Animation::fadeIn(ui->openDBButton, 350);
    Animation::fadeOut(ui->masterKeyEdit, 350);
    Animation::fadeOut(ui->usernameEdit, 350);
    Animation::fadeOut(ui->passwordEdit, 350);
    ui->createDBButton->setEnabled(true);
    ui->openDBButton->setEnabled(true);
    ui->masterKeyEdit->setEnabled(false);
    ui->usernameEdit->setEnabled(false);
    ui->passwordEdit->setEnabled(false);
    ui->masterKeyEdit->clear();
    ui->usernameEdit->clear();
    ui->passwordEdit->clear();
    if (!ui->createButton->isHidden())
    {
        Animation::fadeOut(ui->createButton, 350);
        ui->createButton->hide();
        ui->createButton->setEnabled(false);
    }
    if (!ui->loginButton->isHidden())
    {
        Animation::fadeOut(ui->loginButton, 350);
        ui->createButton->hide();
        ui->createButton->setEnabled(false);
    }
}

void LoginWindow::on_backButton_clicked()
{
    showStartup();
}

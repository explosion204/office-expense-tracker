#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QFileDialog>
#include <QGridLayout>
#include <gui/mainwindow.h>
#include <service/controlunit.h>
#include <service/animation.h>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    /*[Button] Purpose: create database*/
    void on_createDBButton_clicked();
    /*[Button] Purpose: open database*/
    void on_openDBButton_clicked();
    /*[Button] Purpose: create database using credentials from auth edits*/
    void on_createButton_clicked();
    /*[Button] Purpose: log in to database using credentials from auth edits*/
    void on_loginButton_clicked();
    /*[Button] Purpose: hide auth controls and show 'OpenDB' & 'CreateDB' buttons*/
    void on_backButton_clicked();

private:
    Ui::LoginWindow *ui;
    QString db_path;
    /*Purpose: show auth edits as login credentials*/
    void showAuthEdits();
    /*Purpose: show startup buttons (OpenDB' & 'CreateDB')*/
    void showStartup();
};

#endif // LOGINWINDOW_H

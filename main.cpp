#include "gui/loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();
//    MainWindow w;
//    w.show();
    return a.exec();
}

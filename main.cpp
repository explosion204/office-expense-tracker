#include "gui/loginwindow.h"
#include <QApplication>

#include <service/computeunit.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();
    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>
#include <wke.h>
#include "DialogLogin.h"
int main(int argc, char *argv[])
{
    //��ʼ��wke
    wkeInitialize();
    QApplication a(argc, argv);
    DialogLogin w;
    w.show();
    return a.exec();
}

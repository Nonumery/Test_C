#include <QCoreApplication>
#include "nstr.cpp"
#include <string>
#include <QtNetwork/QTcpSocket>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyBuffer buff;
    FirstThread first(buff);
    SecondThread second(buff);

    first.start();
    second.start();

    first.quit();
    second.quit();

    return a.exec();
}

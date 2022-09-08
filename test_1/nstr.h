#ifndef NSTR_H
#define NSTR_H
#include <QString>
#include <iostream>
#include <QThread>
#include <QTextStream>
#include <QMutex>
#include <QWaitCondition>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QTcpSocket>
#include <QHostAddress>

class MyBuffer
{
    QString nums;
    QMutex m;
    QWaitCondition getStr;
public:
    MyBuffer();
    QString getBuff();
    void wait();
    QMutex* mute() { return &m; }
    void setBuff(QString s);
    void clearBuff();
};

class FirstThread: public QThread
{
    MyBuffer& buff;
    void run() override;
public:
    FirstThread(MyBuffer& b, QObject* parent = nullptr);
};


class SecondThread: public QThread
{
    QUdpSocket* socket;
    MyBuffer& buff;
    void run() override;
public:
    SecondThread(MyBuffer& b, QObject* parent = nullptr);

};

#endif // NSTR_H

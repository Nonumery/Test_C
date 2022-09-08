#include "nstr.h"

MyBuffer::MyBuffer()
{
    nums=QString();
}

QString MyBuffer::getBuff()
{
    return nums;
}

void MyBuffer::wait()
{
    getStr.wait(&m);
}

void MyBuffer::setBuff(QString s)
{
    nums=s;
    getStr.notify_one();
}

void MyBuffer::clearBuff()
{
    nums = QString();
}

FirstThread::FirstThread(MyBuffer &b, QObject *parent): QThread(parent), buff(b)
{

}

void FirstThread::run()
{
    QTextStream s(stdin);
    while(true)
    {
        QString str = s.readLine();

        int len = str.length();

        QString reg("^([0-9]){%1}$");
        reg = reg.arg(len);

        if (len > 64 || !str.contains(QRegExp(reg)))
            continue;

        qSort(str.begin(), str.end());
        std::reverse(str.begin(), str.end());

        str.replace(QRegExp("[2,4,6,8,0]"), "KB");

        buff.setBuff(str);
    }
}

SecondThread::SecondThread(MyBuffer &b, QObject *parent): QThread(parent), buff(b)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 9999);
}

void SecondThread::run()
{
    QString str;
    int sum;
    while(true)
    {
        QMutexLocker q(buff.mute());
        buff.wait();

        sum = 0;
        str = buff.getBuff();
        buff.clearBuff();
        if (str.isNull()) continue;

        std::cout << str.toStdString() << std::endl;

        for(int i = 1; i < 10; i+=2)
            sum+=str.count(QString::number(i))*i;
        std::cout << sum << std::endl;

        socket->writeDatagram(str.toUtf8(), QHostAddress::LocalHost, 1234);


    }
}

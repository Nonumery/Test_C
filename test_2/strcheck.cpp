#include "strcheck.h"

StrCheck::StrCheck()
{
    str = QString();
    socket = new QUdpSocket();
    socket->bind(QHostAddress::LocalHost, 1234);

    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(ReadingData()));
}

void StrCheck::check()
{
    int len = str.length();
    if (len > 2 && len%32==0)
        std::cout << "Success!"<< std::endl;
    else
        std::cout << "Error!" << std::endl;
}


void StrCheck::ReadingData()
{
    QHostAddress sender;
    quint16 senderPort;
    while(socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());

        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        str = QString(datagram.data());
        check();
    }
}

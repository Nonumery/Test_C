#ifndef STRCHECK_H
#define STRCHECK_H
#include <iostream>
#include <QString>
#include <QtNetwork/QUdpSocket>
#include <QHostAddress>
#include <QCoreApplication>

class StrCheck: public QObject
{
    Q_OBJECT
private:
    QUdpSocket* socket;
    QString str;
public:
    StrCheck();
    void check();
    virtual ~StrCheck() {};
private slots:
    void ReadingData();
};

#endif // STRCHECK_H

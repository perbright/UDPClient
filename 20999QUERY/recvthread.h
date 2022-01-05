#ifndef RECVTHREAD_H
#define RECVTHREAD_H
#include <QThread>
#include "UDP20999.h"
#include "querytest.h"
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class QUERYTEST; }
QT_END_NAMESPACE

class RecvThread : public QThread
{
     Q_OBJECT
public:
    RecvThread();
    void closeThread();
    void getSock(SOCKET tempSock);
    QTextEdit *textEdit;
protected:
    virtual void run();
private:
    volatile bool isStop;
    Ui::QUERYTEST *ui;
    QString strBuffer;
    UDPClient *UDPT = new UDPClient();
    unsigned char *recvbuff;
    int recvlen = 0;
    unsigned int SendBuffLen;
    SOCKET sClient;
    struct sockaddr_in send_Data_Addr;
    int	nAddrLen_send;
};

#endif // RECVTHREAD_H

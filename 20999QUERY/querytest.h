#ifndef QUERYTEST_H
#define QUERYTEST_H

#include <QMainWindow>
#include "UDP20999.h"
#include "QDateTime"
#include "recvthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QUERYTEST; }
QT_END_NAMESPACE

class QUERYTEST : public QMainWindow
{
    Q_OBJECT

public:
    QUERYTEST(QWidget *parent = nullptr);
    ~QUERYTEST();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();


    void on_lineEdit_6_textEdited(const QString &arg1);

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_4_textEdited(const QString &arg1);

    void on_lineEdit_3_textEdited(const QString &arg1);

    void on_pushButton_4_clicked();

private:
    Ui::QUERYTEST *ui;
    UDPClient *UDPT = new UDPClient();
    WSADATA wsd;
    SOCKET sClient;
    struct sockaddr_in sServAddr;
    struct sockaddr_in sClientAddr;
    struct sockaddr_in send_Data_Addr;
    int	nAddrLen_send;
    int port;
    bool isPortEmpty;

    int a,b,c,d;
    unsigned char *sendbuff;
    unsigned char *recvbuff;

    int	len = 0;
    int recvlen = 0;
    unsigned int nSendBuffLen;
    unsigned int SBuffLen;
    unsigned int SendBuffLen;
    unsigned char DataClassID = 0;	//数据类ID
    unsigned char ObjectID = 0;		//对象ID
    unsigned char AttributeID = 0;	//属性ID
    unsigned char ElementID = 0;	//元素ID
    unsigned char mSendBuff[1024];
    QString strBuffer;
    RecvThread *recvthread;
};
#endif // QUERYTEST_H

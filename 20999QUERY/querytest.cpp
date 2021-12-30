#include "querytest.h"
#include "ui_querytest.h"
#include "QMessageBox"

QUERYTEST::QUERYTEST(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QUERYTEST)
{
    ui->setupUi(this);
}

QUERYTEST::~QUERYTEST()
{
    delete ui;
}


void QUERYTEST::on_pushButton_2_clicked()
{
   if(QMessageBox::Yes == QMessageBox::question(this, "20999查询","确认要退出查询吗？"))
   {

   }
}

void QUERYTEST::on_pushButton_clicked()
{
    QString QueryTitle = "Query消息框";
    QString strInfo = "确定要发送查询报文？";
    QMessageBox::StandardButton defaultBtn=QMessageBox::NoButton;
    QMessageBox::StandardButton result;;
    result=QMessageBox::question(this, QueryTitle, strInfo,
                          QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel,
                          defaultBtn);
    if (result==QMessageBox::Yes)
    {
        memset(mSendBuff,0x00,1024);
        recvbuff = new unsigned char[1024 * 1024];
        memset(recvbuff,0x00,1024 * 1024);
        sendbuff = new unsigned char[1024 * 1024];
        memset(sendbuff,0x00,1024 * 1024);
        UDPT->Crc16_h(DataClassID,ObjectID,AttributeID,ElementID,mSendBuff,SBuffLen);
        sendbuff[nSendBuffLen++] = 0x7E;
        memcpy(sendbuff+nSendBuffLen,mSendBuff,SBuffLen);
        nSendBuffLen = nSendBuffLen + SBuffLen;
        sendbuff[nSendBuffLen++] = 0x7D;
        SendBuffLen = nSendBuffLen;

        len = sendto(sClient, (char *)sendbuff,SendBuffLen,0,(struct sockaddr*)&sServAddr, sizeof(struct sockaddr));
        if (len == SOCKET_ERROR)
        {
            ui->textEdit->append("send error!");
            //cout<<"send error!"<<endl;
            closesocket(sClient);
            WSACleanup();
            Sleep(1000);
        }
        else
        {
            QString str1 = "send success and len is ";
            QString str = str1 + len;
            ui->textEdit->append(str);
            //cout<<"send success and len is "<<len<<endl;
        }
        recvlen = recvfrom(sClient, (char *)recvbuff, 1024, 0,(struct sockaddr*)&send_Data_Addr,&nAddrLen_send);
        if (SOCKET_ERROR == recvlen)
        {
            ui->textEdit->append("recv error!");
            //cout<<"recv error!"<<endl;
            closesocket(sClient);
            WSACleanup();
            Sleep(1000);
        }
        QString strResult;
        strResult = UDPT->hexToString(recvbuff,recvlen);
        ui->textEdit->append(strResult);
    }
    else if(result==QMessageBox::No)
    {

    }
    else
    {

    }
}

void QUERYTEST::on_pushButton_3_clicked()
{
    if(!isPortEmpty)
    {
        memset(&sServAddr, 0, sizeof(sServAddr));
        memset(&sClientAddr, 0, sizeof(sClientAddr));
        sServAddr.sin_family = AF_INET;
        sServAddr.sin_port = htons(port);
        sServAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        sClientAddr.sin_family = AF_INET;
        sClientAddr.sin_port = htons(4001);
        sClientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        if (WSAStartup(MAKEWORD(2,2),&wsd) != 0)
        {
            ui->textEdit->append("WSAStartup failed!");
            //cout<<"WSAStartup failed!"<<endl;
        }

        sClient = socket(AF_INET, SOCK_DGRAM,IPPROTO_UDP);
        if (INVALID_SOCKET == sClient)
        {
            ui->textEdit->append("socket failed!");
            //cout<<"socket failed!"<<endl;
            WSACleanup();
            Sleep(1000);
        }
        else
        {
            ui->textEdit->append("Client UDP Socket init");
            //cout<<"Client UDP Socket init"<<endl;
        }

        if (bind(sClient,(struct sockaddr *)&sClientAddr, sizeof(sClientAddr)) == SOCKET_ERROR)
        {
            ui->textEdit->append("bind failed!");
            //cout<<"bind failed!"<<endl;
            closesocket(sClient);
            WSACleanup();
            Sleep(1000);
        }
        else
        {
            ui->textEdit->append("Client UDP Socket bind IP & Port !");
            //cout << "Client UDP Socket bind IP & Port !" << endl;
        }
    }
}


void QUERYTEST::on_lineEdit_6_textEdited(const QString &arg1)
{
    if(arg1.isEmpty())
    {
        isPortEmpty = true;
    }
    else
    {
        port = arg1.toInt();
        isPortEmpty = false;
    }
}

void QUERYTEST::on_lineEdit_textEdited(const QString &arg1)
{
    a = arg1.toInt();
    DataClassID = a;
}

void QUERYTEST::on_lineEdit_2_textEdited(const QString &arg1)
{
    b = arg1.toInt();
    ObjectID = b;
}

void QUERYTEST::on_lineEdit_4_textEdited(const QString &arg1)
{
    c = arg1.toInt();
    AttributeID = c;
}

void QUERYTEST::on_lineEdit_3_textEdited(const QString &arg1)
{
    d = arg1.toInt();
    ElementID = d;
}

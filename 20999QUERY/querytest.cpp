#include "querytest.h"
#include "ui_querytest.h"
#include "QMessageBox"
#include "QDateTime"
#include "recvthread.h"

QUERYTEST::QUERYTEST(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QUERYTEST)
{
    ui->setupUi(this);
    this->setWindowTitle("20999查询工具");
}

QUERYTEST::~QUERYTEST()
{
    delete ui;
}


void QUERYTEST::on_pushButton_2_clicked()
{
   if(QMessageBox::Yes == QMessageBox::question(this, "20999查询","确认要退出查询吗？"))
   {
       recvthread->closeThread();
       recvthread->wait();
       closesocket(sClient);
       WSACleanup();
       close();
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
        nSendBuffLen = 0;
        SBuffLen = 0;
        SendBuffLen = 0;
        nAddrLen_send = sizeof(send_Data_Addr);
        memset(mSendBuff,0x00,1024);
        recvbuff = new unsigned char[1024 * 1024];
        memset(recvbuff,0x00,1024 * 1024);
        sendbuff = new unsigned char[1024 * 1024];
        memset(sendbuff,0x00,1024 * 1024);
        DataClassID = a;
        ObjectID = b;
        AttributeID = c;
        ElementID = d;
        UDPT->Crc16_h(DataClassID,ObjectID,AttributeID,ElementID,mSendBuff,SBuffLen);
        sendbuff[nSendBuffLen++] = 0x7E;
        memcpy(sendbuff+nSendBuffLen,mSendBuff,SBuffLen);
        nSendBuffLen = nSendBuffLen + SBuffLen;
        sendbuff[nSendBuffLen++] = 0x7D;
        SendBuffLen = nSendBuffLen;
        len = sendto(sClient, (char *)sendbuff,SendBuffLen,0,(struct sockaddr*)&sServAddr, sizeof(struct sockaddr));
        if (len == SOCKET_ERROR)
        {
            QString str;
            QDateTime time;
            time = QDateTime::currentDateTime();
            str = time.toString("(yyyy-MM-dd hh:mm:ss)");
            strBuffer.append(str);
            strBuffer.append(0x20);
            strBuffer = strBuffer + ":" + "send error!";
            ui->textEdit->append(strBuffer);
            //ui->textEdit->append("send error!");
            //cout<<"send error!"<<endl;
            //closesocket(sClient);
            //WSACleanup();
            Sleep(100);
        }
        else
        {
            QString strp;
            QDateTime time;
            strBuffer.clear();
            time = QDateTime::currentDateTime();
            strp = time.toString("(yyyy-MM-dd hh:mm:ss)");
            strBuffer.append(strp);
            strBuffer.append(0x20);

            QString str1 = "send success and len is ";
            QString sLen = QString::number(len);
            QString str = str1 + sLen;
            strBuffer = strBuffer + ":" + str;
            ui->textEdit->append(strBuffer);
            //cout<<"send success and len is "<<len<<endl;
        }
        /*recvlen = recvfrom(sClient, (char *)recvbuff, 1024, 0,(struct sockaddr*)&send_Data_Addr,&nAddrLen_send);
        if (SOCKET_ERROR == recvlen)
        {
            QString strp;
            QDateTime time;
            strBuffer.clear();
            time = QDateTime::currentDateTime();
            strp = time.toString("(yyyy-MM-dd hh:mm:ss)");
            strBuffer.append(strp);
            strBuffer.append(0x20);
            strBuffer = strBuffer + ":" + "recv error!";
            ui->textEdit->append(strBuffer);
            //ui->textEdit->append("recv error!");
            //cout<<"recv error!"<<endl;
            //closesocket(sClient);
            //WSACleanup();
            Sleep(100);
        }
        else
        {
            QString strResult;
            QString strp;
            QDateTime time;
            strBuffer.clear();
            time = QDateTime::currentDateTime();
            strp = time.toString("(yyyy-MM-dd hh:mm:ss)");
            strBuffer.append(strp);
            strBuffer.append(0x20);
            strResult = UDPT->hexToString(recvbuff,recvlen);
            strBuffer = strBuffer + ":" + strResult;
            ui->textEdit->append(strBuffer);
            //ui->textEdit->append(strResult);
        }*/
        delete[] sendbuff;
        //delete[] recvbuff;
    }
    else if(result==QMessageBox::No)
    {
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
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
            QString strp;
            QDateTime time;
            strBuffer.clear();
            time = QDateTime::currentDateTime();
            strp = time.toString("(yyyy-MM-dd hh:mm:ss)");
            strBuffer.append(strp);
            strBuffer.append(0x20);
            strBuffer = strBuffer + ":" + "WSAStartup failed!";
            ui->textEdit->append(strBuffer);
            //ui->textEdit->append("WSAStartup failed!");
            //cout<<"WSAStartup failed!"<<endl;
        }

        sClient = socket(AF_INET, SOCK_DGRAM,IPPROTO_UDP);
        if (INVALID_SOCKET == sClient)
        {
            QString strp;
            QDateTime time;
            strBuffer.clear();
            time = QDateTime::currentDateTime();
            strp = time.toString("(yyyy-MM-dd hh:mm:ss)");
            strBuffer.append(strp);
            strBuffer.append(0x20);
            strBuffer = strBuffer + ":" + "socket failed!";
            ui->textEdit->append(strBuffer);
            //ui->textEdit->append("socket failed!");
            //cout<<"socket failed!"<<endl;
            WSACleanup();
            Sleep(1000);
        }
        else
        {
            QString strp;
            QDateTime time;
            strBuffer.clear();
            time = QDateTime::currentDateTime();
            strp = time.toString("(yyyy-MM-dd hh:mm:ss)");
            strBuffer.append(strp);
            strBuffer.append(0x20);
            strBuffer = strBuffer + ":" + "Client UDP Socket init";
            ui->textEdit->append(strBuffer);
            //ui->textEdit->append("Client UDP Socket init");
            //cout<<"Client UDP Socket init"<<endl;
        }

        if (bind(sClient,(struct sockaddr *)&sClientAddr, sizeof(sClientAddr)) == SOCKET_ERROR)
        {
            QString strp;
            QDateTime time;
            strBuffer.clear();
            time = QDateTime::currentDateTime();
            strp = time.toString("(yyyy-MM-dd hh:mm:ss)");
            strBuffer.append(strp);
            strBuffer.append(0x20);
            strBuffer = strBuffer + ":" + "bind failed!";
            ui->textEdit->append(strBuffer);
            //ui->textEdit->append("bind failed!");
            //cout<<"bind failed!"<<endl;
            closesocket(sClient);
            WSACleanup();
            Sleep(1000);
        }
        else
        {
            QString strp;
            QDateTime time;
            strBuffer.clear();
            time = QDateTime::currentDateTime();
            strp = time.toString("(yyyy-MM-dd hh:mm:ss)");
            strBuffer.append(strp);
            strBuffer.append(0x20);
            strBuffer = strBuffer + ":" + "Client UDP Socket bind IP & Port !";
            ui->textEdit->append(strBuffer);
            //ui->textEdit->append("Client UDP Socket bind IP & Port !");
            //cout << "Client UDP Socket bind IP & Port !" << endl;
        }
        //RecvThread *recvthread = new RecvThread;
        recvthread = new RecvThread;
        recvthread->textEdit = ui->textEdit;
        recvthread->getSock(sClient);
        recvthread->start();
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
    //DataClassID = a;
}

void QUERYTEST::on_lineEdit_2_textEdited(const QString &arg1)
{
    b = arg1.toInt();
    //ObjectID = b;
}

void QUERYTEST::on_lineEdit_4_textEdited(const QString &arg1)
{
    d = arg1.toInt();
    //AttributeID = c;
}

void QUERYTEST::on_lineEdit_3_textEdited(const QString &arg1)
{
    c = arg1.toInt();
    //ElementID = d;
}

void QUERYTEST::on_pushButton_4_clicked()
{
    if(QMessageBox::Yes == QMessageBox::question(this, "清空界面","确认要清空交互界面吗？"))
    {
         ui->textEdit->clear();
    }
}

#include "recvthread.h"

RecvThread::RecvThread()
{
    textEdit = new QTextEdit;
    isStop = false;
}

void RecvThread::closeThread()
{
    isStop = true;
}

void RecvThread::getSock(SOCKET tempSock)
{
    sClient = tempSock;
}

void RecvThread::run()
{
    while (!isStop)
    {
        nAddrLen_send = sizeof(send_Data_Addr);
        recvbuff = new unsigned char[1024 * 1024];
        memset(recvbuff,0x00,1024 * 1024);
        recvlen = recvfrom(sClient, (char *)recvbuff, 1024, 0,(struct sockaddr*)&send_Data_Addr,&nAddrLen_send);
        if (SOCKET_ERROR == recvlen)
        {
            //QString strp;
            //QDateTime time;
            //strBuffer.clear();
            //time = QDateTime::currentDateTime();
            //strp = time.toString("(yyyy-MM-dd hh:mm:ss)");
            //strBuffer.append(strp);
            //strBuffer.append(0x20);
            //strBuffer = strBuffer + ":" + "recv error!";
            //textEdit->append(strBuffer);
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
            textEdit->append(strBuffer);
            //ui->textEdit->append(strResult);
        }
    }
}

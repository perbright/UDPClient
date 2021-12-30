#ifndef UDP20999_H
#define UDP20999_H

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <WinSock2.h>
#include <Windows.h>
#include <QMainWindow>
using namespace std;

#define START				0x7E;
#define END					0x7D;
#define AGREEMENT_VERSION	0x0101;
#define HOST_ID				0x01;
#define ATC_ID				0x00000000;
#define ROAD_ID				0x00

typedef enum tagFrameType_GB20999
{
    FRAME_TYPE_QUERY                = 0x10,    //查询1
    FRAME_TYPE_QUERY_REPLY          = 0x20,    //查询应答2
    FRAME_TYPE_QUERY_ERRORREPLY     = 0x21,    //查询出错回复3
    FRAME_TYPE_SET                  = 0x30,    //设置4
    FRAME_TYPE_SET_REPLY            = 0x40,    //设置应答5
    FRAME_TYPE_SET_ERRORREPLY       = 0x41,    //设置出错回复6
    FRAME_TYPE_BROADCAST            = 0x50,    //广播7
    FRAME_TYPE_TRAP                 = 0x60,    //主动上报8
    FRAME_TYPE_HEART_QUERY          = 0x70,    //心跳查询9
    FRAME_TYPE_HEART_REPLY          = 0x80,    //心跳应答10
}EFrameType_GB20999;

class UDPClient
{
public:
    UDPClient();
    ~UDPClient();
    void Crc16_h(unsigned char nDataClassID,unsigned char nObjectID,unsigned char nAttributeID,unsigned char nElementID,unsigned char *sendtempbuff,unsigned int &BuffLen);

    QString hexToString(unsigned char *in, int len);
private:
    unsigned short Crc16(const unsigned char *buffer, int buffer_length);
};

#endif // UDP20999_H

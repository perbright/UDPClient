#include"UDP20999.h"
UDPClient::UDPClient()
{

}

UDPClient::~UDPClient()
{

}

unsigned short UDPClient::Crc16(const unsigned char *buffer, int buffer_length)
{
    short usRc = 0;
    unsigned char i = 0;
    short usCrc16 = 0x0000;
    while (buffer_length--)
    {
        for (i = 0x80; i != 0; i >>= 1)
        {
            if ((usCrc16 & 0x8000) != 0)
            {
                usCrc16 = usCrc16 << 1;
                usCrc16 = usCrc16 ^ 0x1005;//x16+x12+x2+1
            }
            else
            {
                usCrc16 = usCrc16 << 1;
            }
            if ((*buffer & i) != 0)
            {
                usCrc16 = usCrc16 ^ 0x1005;//x16+x12+x2+1
            }
        }
        buffer++;
    }
    return usCrc16;
}

void UDPClient::Crc16_h(unsigned char nDataClassID, unsigned char nObjectID, unsigned char nAttributeID, unsigned char nElementID, unsigned char *sendtempbuff, unsigned int &BuffLen)
{
    unsigned char FrameID;
        unsigned short nCrc16;
        unsigned char m_chSendBuff[1024];
        unsigned int dwSendBuffLen;
        unsigned int dwTempSendBuffLen;
        memset(m_chSendBuff,0x00,1024);
        dwSendBuffLen = 0;
        FrameID = 0x01;

        m_chSendBuff[dwSendBuffLen++] = 0x00;
        m_chSendBuff[dwSendBuffLen++] = 0x00;
        m_chSendBuff[dwSendBuffLen++] = 0x01;
        m_chSendBuff[dwSendBuffLen++] = 0x01;
        m_chSendBuff[dwSendBuffLen++] = HOST_ID;
        m_chSendBuff[dwSendBuffLen++] = 0x00;
        m_chSendBuff[dwSendBuffLen++] = 0x00;
        m_chSendBuff[dwSendBuffLen++] = 0x00;
        m_chSendBuff[dwSendBuffLen++] = 0x00;
        m_chSendBuff[dwSendBuffLen++] = ROAD_ID;
        m_chSendBuff[dwSendBuffLen++] = FrameID;

        //查询
        m_chSendBuff[dwSendBuffLen++] = FRAME_TYPE_QUERY;
        m_chSendBuff[dwSendBuffLen++] = 0x01;
        m_chSendBuff[dwSendBuffLen++] = 0x01;
        m_chSendBuff[dwSendBuffLen++] = 0x04;
        m_chSendBuff[dwSendBuffLen++] = nDataClassID;
        m_chSendBuff[dwSendBuffLen++] = nObjectID;
        m_chSendBuff[dwSendBuffLen++] = nAttributeID;
        m_chSendBuff[dwSendBuffLen++] = nElementID;

        dwTempSendBuffLen = dwSendBuffLen;
        short nPacketLen = htons(dwTempSendBuffLen);
        memcpy(m_chSendBuff, &nPacketLen, 2);

        nCrc16 = Crc16(m_chSendBuff, dwSendBuffLen);
        nCrc16 = htons(nCrc16);
        memcpy(m_chSendBuff + dwSendBuffLen, &nCrc16, 2);
        dwSendBuffLen += 2;
        memcpy(sendtempbuff,m_chSendBuff,dwSendBuffLen);
        BuffLen = dwSendBuffLen;
}

QString UDPClient::hexToString(unsigned char *in, int len)
{
    int i;
    unsigned char inchar,hi,lo;
    QString s;
    for(i=0; i<len; i++)
    {
        inchar = in[i];
        hi = (inchar & 0xF0)>>4;
        if(hi > 9)
        {
            hi = 'A' + (hi - 0x0A);
        }
        else
        {
            hi += 0x30;
        }
        s.append(hi);

        lo = inchar & 0x0F;
        if(lo>9)
        {
            lo = 'A' + (lo - 0x0A);
        }
        else
        {
            lo += 0x30;
        }
        s.append(lo);

        s.append(0x20); //空格
    }
    return s;
}

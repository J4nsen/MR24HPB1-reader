#include "radarframe.h"
#include <QDebug>
#include <QVariant>
#include <QByteArray>

RadarFrame::RadarFrame(QByteArray raw_frame, QObject *parent)
    : QObject{parent}
{
    qDebug() << this << raw_frame.toHex();

    quint16 frame_size = ((quint16)raw_frame.at(2) << 8) | (quint16)raw_frame.at(1);

    unsigned char functionCode = raw_frame.at(3);
    unsigned char addressCode1 = raw_frame.at(4);
    unsigned char addressCode2 = raw_frame.at(5);
    m_data = raw_frame.mid(6, frame_size-7);

    m_crcLow = raw_frame.at(raw_frame.size()-2);
    m_crcHigh = raw_frame.at(raw_frame.size()-1);

//    qDebug() << QByteArray(1, m_crcLow).toHex();
//    qDebug() << QByteArray(1, m_crcHigh).toHex();


    switch(functionCode){
    case 1:
        m_functionCode = RadarFrame::READ_COMMAND;
        break;
    case 2:
        m_functionCode = RadarFrame::COPY_ORDER;
        break;
    case 3:
        m_functionCode = RadarFrame::PASSIV_REPORTING;
        break;
    case 4:
        m_functionCode = RadarFrame::PROACTIVE_REPORTING;

        switch(addressCode1){
        case 3:
            m_addressCodes1 = RadarFrame::REPORT_RADAR_INFO;
            switch(addressCode2){
            case 5:
                m_addressCodes2 = RadarFrame::ENVIRONTMENT_STATUS;
                break;
            case 6:
                m_addressCodes2 = RadarFrame::MOTOR_SIGNS;
                break;
            case 7:
                m_addressCodes2 = RadarFrame::APPROCHING_AWAY;
                break;
            }

            break;
        case 5:
            m_addressCodes1 = RadarFrame::REPORT_OTHER_INFO;
            switch(addressCode2){
            case 1:
                m_addressCodes2 = RadarFrame::HEARTBEAT_PACK;
                break;
            case 2:
                m_addressCodes2 = RadarFrame::ABNORMAL_RESET;
                break;
            }

            break;
        }

        break;
    }
    //qDebug() << m_functionCode;
    //qDebug() << m_addressCodes1;
    //qDebug() << m_addressCodes2;
    //qDebug() << m_data.toHex();

    if(m_functionCode == RadarFrame::PROACTIVE_REPORTING && m_addressCodes1 == RadarFrame::REPORT_RADAR_INFO && m_addressCodes2 == RadarFrame::MOTOR_SIGNS){
        Float_Byte fb;
        fb.Byte[0] = m_data[0];
        fb.Byte[1] = m_data[1];
        fb.Byte[2] = m_data[2];
        fb.Byte[3] = m_data[3];
        qDebug() << "Motor" << fb.Float;
    }
}


//static unsigned short int us_CalculateCrc16(unsigned char *lpuc_Frame, unsigned short int lus_Len)
//{
//    unsigned char luc_CRCHi = 0xFF;
//    unsigned char lu

//    while(lus_Len--)
//    {
//        li_Index = luc_CRCLo ^ *( lpuc_Frame++);
//        luc_CRCLo = (unsigned char)( luc_CRCHi ^ cuc_CRCHi[li_Index]);
//        luc_CRCHi = cuc_CRCLo[li_Index];
//    }
//    return (unsigned short int )(luc_CRCLo << 8 | luc_CRCHi);
//}

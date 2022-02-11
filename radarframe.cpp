#include "radarframe.h"
#include <QDebug>
#include <QVariant>

RadarFrame::RadarFrame(QByteArray raw_frame, QObject *parent)
    : QObject{parent}
{
    qDebug() << this << raw_frame.toHex();

    quint16 frame_size = ((quint16)raw_frame.at(2) << 8) | (quint16)raw_frame.at(1);

    unsigned char functionCode = raw_frame.at(3);
    unsigned char addressCode1 = raw_frame.at(4);
    unsigned char addressCode2 = raw_frame.at(5);
    m_data = raw_frame.mid(6, frame_size-7);

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
    qDebug() << m_functionCode;
    qDebug() << m_addressCodes1;
    qDebug() << m_addressCodes2;
    qDebug() << m_data.toHex();
}

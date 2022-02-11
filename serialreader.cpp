#include "serialreader.h"
#include <QDebug>

SerialReader::SerialReader(QString serialPort, QObject *parent)
    : QObject{parent}
{
    qDebug() << "New serial Reader";

    m_serialport = new QSerialPort();
    m_serialport->setBaudRate(QSerialPort::Baud9600);

    m_serialport->setPortName(serialPort);
    if(!m_serialport->open(QIODevice::ReadOnly)){
        qDebug() << "Could not open port: " + serialPort;
    }
    else{
        QObject::connect(m_serialport, &QSerialPort::readyRead, this, &SerialReader::on_readyRead);
        QObject::connect(this, &SerialReader::newFrame, this, &SerialReader::on_newFrame);
    }
}

void SerialReader::on_readyRead()
{

    //qDebug() << this << "on_readyRead()";
    m_buffer.append(m_serialport->readAll());
    //qDebug() << m_buffer.toHex();
    for(int i = 0; i < m_buffer.size(); i++){
        // Search for start in buffer
        if(m_buffer.at(i) == 0x55){
            //qDebug() << "Found start at" << i;
            // Can we read the size of the frame?
            if(m_buffer.size() > i+2){
                // Can we read the whole frame?
                quint16 frame_size = ((quint16)m_buffer.at(i+2) << 8) | (quint16)m_buffer.at(i+1);
                if(m_buffer.size() > i+frame_size){
                    m_frame = m_buffer.mid(i, i + frame_size);
                    emit newFrame(m_frame);

                    // Resize buffer
                    m_buffer = m_buffer.mid(i + frame_size);
                    return;
                }
                else return;

            }
            else return;
        }
    }

}

void SerialReader::on_newFrame(QByteArray frame)
{
    //qDebug() << this << "on_newFrame" << frame.toHex();
    m_radarFrameList.append(new RadarFrame(frame));
}


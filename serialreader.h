#ifndef SERIALREADER_H
#define SERIALREADER_H

#include <QObject>
#include <QtSerialPort>
#include <QByteArray>
#include <QList>
#include "radarframe.h"

class SerialReader : public QObject
{
    Q_OBJECT
public:
    explicit SerialReader(QString serialPort, QObject *parent = nullptr);
    QSerialPort *m_serialport;
    QByteArray m_buffer;
    QByteArray m_frame;
    QList<RadarFrame*> m_radarFrameList;
signals:
    void newFrame(QByteArray frame);

private slots:
    void on_readyRead();
    void on_newFrame(QByteArray frame);
};

#endif // SERIALREADER_H

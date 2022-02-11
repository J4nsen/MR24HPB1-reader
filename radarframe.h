#ifndef RADARFRAME_H
#define RADARFRAME_H

#include <QObject>
#include <QByteArray>

class RadarFrame : public QObject
{
    Q_OBJECT
public:
    explicit RadarFrame(QByteArray raw_frame, QObject *parent = nullptr);

    enum FunctionCodes{
        READ_COMMAND,
        COPY_ORDER,
        PASSIV_REPORTING,
        PROACTIVE_REPORTING,
    };
    Q_ENUM(FunctionCodes);
    FunctionCodes m_functionCode;

    enum AddressCodes1{
        MARKING_SEARCH,
        RADAR_INFO,
        SYSTEM_PARAMETER,
        OTHER,
        REPORT_MODULE_INFO,
        REPORT_RADAR_INFO,
        REPORT_SYSTEM_INFO,
        REPORT_OTHER_INFO
    };
    Q_ENUM(AddressCodes1);
    AddressCodes1 m_addressCodes1;

    enum AddressCodes2{
        DEVICE_ID,
        SOFTWARE_VERSION,
        HARDWARE_VERSION,
        PROTOCOL_VERSION,
        ENVIRONTMENT_STATUS,
        SIGNS_PARAMTERS,
        THRESHOLD_GEAR,
        SCENE_SETTING,
        REBOOT,
        MOTOR_SIGNS,
        APPROCHING_AWAY,
        HEARTBEAT_PACK,
        ABNORMAL_RESET
    };
    Q_ENUM(AddressCodes2);
    AddressCodes2 m_addressCodes2;

    QByteArray m_data;


private:

signals:

};

#endif // RADARFRAME_H

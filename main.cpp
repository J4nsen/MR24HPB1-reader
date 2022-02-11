#include <QCoreApplication>
#include <QCommandLineParser>
#include "serialreader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("Seeed 24GHz Radar Serial Reader");
    QCoreApplication::setApplicationVersion("0.1");


    QCommandLineParser parser;
    parser.setApplicationDescription("Read serial data of a Seeed 24GHz Radar Sensor");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption portOption("p", "port", "Serial port to read from.");
    parser.addOption(portOption);

    // Process the actual command line arguments given by the user
    parser.process(a);


    if (!parser.isSet(portOption)) {
        qWarning() << "You need to set a serial port with -p.";
    }
    else{
        QString serialPort = parser.value(portOption);
        qDebug() << serialPort;
        new SerialReader(serialPort);
        return a.exec();
    }
}

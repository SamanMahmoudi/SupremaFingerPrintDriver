#ifndef DRIVERFINGER_H
#define DRIVERFINGER_H
#include <QSerialPort>
#include <QDebug>
#include <QObject>
#include <QLabel>
#include <QThread>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QTimer>
#include <QSqlError>
#include <QTime>
#include <QSqlRecord>
#include <QSerialPortInfo>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QSound>
#include <QWaitCondition>
#include "suprema.h"

class DriverFinger : public QWidget
{
    Q_OBJECT
private:
     DriverFinger();
     static DriverFinger *_instance;
     int ArrayHextoInt(QByteArray HexStream);
     char command[13];
     char addr [4];
     char size[4];
     char param[4];
     QString mSource;
     bool EnrollFlag = false;
     bool IsActiveEmpNo = false;
     int counter=1;
     bool DeviceIsNotActive = false;
     QEventLoop _loop;
     QTimer timer;

public:
     static DriverFinger *GetInstance();
    ~DriverFinger();
public:
    int inBytesExpecteddd = 398;
    char bufff[398];
    char buf[26];
    int inBytesExpected = 26;
    char tempbuf[385];
    QString readS;
    QString lb;
    int SendDataInt;
    Q_INVOKABLE void WriteM (QString te);
    Q_INVOKABLE char calc_checksum_D (char *commd,int num);
    Q_INVOKABLE void enroll_by_scan_req_D(QString Num);
    Q_INVOKABLE int delete_All_Templates_D();
    Q_INVOKABLE int Read_template(long int,int Roll);
    Q_INVOKABLE int number_of_Enrolled_FingerPrint();
    Q_INVOKABLE int backint(QString st);
    Q_INVOKABLE void SendToTrafficAdmin(QString num);
    Q_INVOKABLE void numbersOfTemplatesforUser(QString numString);
    Q_INVOKABLE int Enroll_by_temp_req_D(long int adr,QByteArray temp);
    Q_INVOKABLE  int Delete_template (long int adr);

    QByteArray Template;
    int select;
    int identifyyy = 0;
    QSqlDatabase dbTemp;
    QSqlDatabase dbDatafile;
    int Device_Num;

    QByteArray *responseData;
    QString *inputCase;
    QString FingerPrintTemplate;
    QByteArray FingerPrintTemplateByteArray;

    int NumbersOfTemplate = -1;

public slots:
    void recieve();
    void quitLoop();
public:
     QSerialPort *serialme1;
signals:
    void sendFingerTemplateToService(QString fingerTemplate);
    void sendAckofEnroll(QString Msg, int Val);
};

#endif // DRIVERFINGER_H

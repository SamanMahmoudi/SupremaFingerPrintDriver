#include "driverfinger.h"
#include <QElapsedTimer>
#include <QMessageBox>
#include <QWaitCondition>

DriverFinger* DriverFinger::_instance = 0;

DriverFinger::DriverFinger()
{
    select = 1;
    responseData = new QByteArray;
    inputCase = new QString;
    serialme1 = new QSerialPort(this);
    serialme1->setPortName("/dev/ttyUSB0");
    serialme1->setBaudRate(QSerialPort::Baud115200);
    serialme1->setDataBits(QSerialPort::Data8);
    serialme1->setParity(QSerialPort::NoParity);
    serialme1->setStopBits(QSerialPort::OneStop);
    serialme1->setFlowControl(QSerialPort::NoFlowControl);
    connect(serialme1,SIGNAL(readyRead()),this,SLOT(recieve()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(quitLoop()));
    if (serialme1->open(QIODevice::ReadWrite))
        qDebug() << "opend";
}

DriverFinger::~DriverFinger()
{
    delete responseData;
    delete inputCase;
}

void DriverFinger::WriteM(QString te)
{

    QByteArray *s = new QByteArray;
    *s = QByteArray::fromHex(te.toUtf8());
    qDebug() << "Write the :" << te;
    writeFile("Write to Suprema >>>>>>>> " + te + "   >>>>>>>>>> " + QDateTime::currentDateTime().toString());

    serialme1->write(*s);
    serialme1->flush();
    delete s;
}

char DriverFinger::calc_checksum_D(char *commd, int num)
{

    int *sum = new int;
    *sum = 0x00;
    int *length = new int;
    *length = num - 2;
    int i;
    for (i=0; i <= *length; i++)
      *sum += commd[i];
    SendDataInt = *sum;

    delete sum;
    delete length;

    return char(SendDataInt);
}

void DriverFinger::enroll_by_scan_req_D(QString Num)
{
    if (Num.toLong() < 4294967295) {
        long int *EmployeNumber = new long int;
        *EmployeNumber = Num.toLong();
        if (!serialme1->open(QIODevice::ReadWrite))
            serialme1->open(QIODevice::ReadWrite);

    /* Start to Create Command to Write into Suprema Fingerprint */
            command[0] = START;
            command[1] = ES;
            command[2] = char (*EmployeNumber & 0xff);
            command[3] = char (*EmployeNumber/256 & 0xff);
            command[4] = char (*EmployeNumber/65536 & 0xff);
            command[5] = char (*EmployeNumber/16777216 & 0xff);
            command[6] = 0x00;
            command[7] = 0x00;
            command[8] = 0x00;
            command[9] = 0x00;
            command[10] = ADD_NEW;
            command[11] = calc_checksum_D (command,12);
            command[12] = END;
    /* End of Creating Command to Write into Suprema Fingerprint */
        QByteArray *databuf1 = new QByteArray;
        *databuf1 = QByteArray((char*)command, 13);
        QString *test = new QString;
        *test = databuf1->toHex();
        WriteM(*test);

        delete databuf1;
        delete test;
        delete EmployeNumber;
    }
}

int DriverFinger::delete_All_Templates_D()
{

    if (!serialme1->open(QIODevice::ReadWrite))
        serialme1->open(QIODevice::ReadWrite);
/* Start to Create Command to Write into Suprema Fingerprint */
        command[0] = START;
        command[1] = DA;
        command[2] = 0x00;
        command[3] = 0x00;
        command[4] = 0x00;
        command[5] = 0x00;
        command[6] = 0x00;
        command[7] = 0x00;
        command[8] = 0x00;
        command[9] = 0x00;
        command[10] = 0x00;
        command[11] = calc_checksum_D (command,12);
        command[12] = END;
/* End of Creating Command to Write into Suprema Fingerprint */

    QByteArray *databuf1 = new QByteArray;
    *databuf1 = QByteArray((char*)command, 13);
    QString *test = new QString;
    *test = databuf1->toHex();
    WriteM(*test);

    delete databuf1;
    delete test;

    return 1;
}

int DriverFinger::Read_template(long int adr,int Roll)
{
    mutex.lock();
    QString *test = new QString;
    QByteArray *databuf1 = new QByteArray;
    try {
        if (!serialme1->open(QIODevice::ReadWrite))
            serialme1->open(QIODevice::ReadWrite);
        select = 2;
        RollTe = Roll;
    /* Start to Create Command to Write into Suprema Fingerprint */
            command[0] = START;
            command[1] = RT;
            command[2] = char (adr & 0xff);
            command[3] = char (adr/256 & 0xff);
            command[4] = char (adr/65536 & 0xff);
            command[5] = char (adr/16777216 & 0xff);
            command[6] = 0x00;
            command[7] = 0x00;
            command[8] = 0x00;
            command[9] = 0x00;
            command[10] = 0x00;
            command[11] = calc_checksum_D (command,12);
            command[12] = END;
    /* End of Creating Command to Write into Suprema Fingerprint */
        *databuf1 = QByteArray((char*)command, 13);
        *test = *databuf1->toHex();
        WriteM(QByteArray((char*)command, 13).toHex());
        timer.start(2000);
        _loop.exec();
        delete databuf1;
        delete test;
        mutex.unlock();
        return 1;
    } catch (...) {
        delete databuf1;
        delete test;
        mutex.unlock();
        return 1;
    }
}

int DriverFinger::number_of_Enrolled_FingerPrint()
{
    QString *test = new QString;
    QByteArray *databuf1 = new QByteArray;
    try {
        if (!serialme1->open(QIODevice::ReadWrite))
            serialme1->open(QIODevice::ReadWrite);
            command[0] = START;
            command[1] = SR;
            command[2] = 0x00;
            command[3] = 0x00;
            command[4] = 0x00;
            command[5] = 0x00;
            command[6] = 0x00;
            command[7] = 0x00;
            command[8] = 0x00;
            command[9] = 0x00;
            command[10] = NumberEnrolledFinger;
            command[11] = calc_checksum_D (command,12);
            command[12] = END;
        *databuf1 = QByteArray((char*)command, 13);
        *test = *databuf1->toHex();
        WriteM(QByteArray((char*)command, 13).toHex());
        timer.start(2000);
        _loop.exec();

        delete databuf1;
        delete test;
         return 1;
    } catch (...) {
        delete databuf1;
        delete test;
         return 1;
    }

}

void DriverFinger::numbersOfTemplatesforUser(QString numString)
{
    mutex.lock();
    long int *num = new long int;
    *num = numString.toLong();
    QString *test = new QString;
    QByteArray *databuf1 = new QByteArray;
    try {
        if (!serialme1->open(QIODevice::ReadWrite))
            serialme1->open(QIODevice::ReadWrite);
    /* Start to Create Command to Write into Suprema Fingerprint */
            command[0] = START;
            command[1] = CT;
            command[2] = char (*num & 0xff);
            command[3] = char (*num/256 & 0xff);
            command[4] = char (*num/65536 & 0xff);
            command[5] = char (*num/16777216 & 0xff);
            command[6] = 0x00;
            command[7] = 0x00;
            command[8] = 0x00;
            command[9] = 0x00;
            command[10] = 0x00;
            command[11] = calc_checksum_D (command,12);
            command[12] = END;
    /* End of Creating Command to Write into Suprema Fingerprint */
        *databuf1 = QByteArray((char*)command, 13);
        *test = databuf1->toHex();
        WriteM(*test);
        delete test;
        delete databuf1;
        mutex.unlock();
    } catch (...) {
        delete test;
        delete databuf1;
        mutex.unlock();
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////

int DriverFinger::Enroll_by_temp_req_D(long int adr, QByteArray temp)
{
    mutex.lock();
    int *size_temp = new int;
    int *temp2 = new int;
    QByteArray *databuf1 = new QByteArray;
    QByteArray *databuf2 = new QByteArray;
    QString *test = new QString;
    try {
        if (!serialme1->open(QIODevice::ReadWrite))
            serialme1->open(QIODevice::ReadWrite);
        int *size_temp = new int;
        *size_temp = temp.size()-1;

        *temp2 = *size_temp;
        *temp2 = *temp2 & (short)0xff00;
        *temp2 = *temp2 >> 8;
        size[0] = (char) *temp2;
        size[1] = (char) ((short) 0xff & (*size_temp));
        size[2] = 0x00;
        size[3] = 0x00;
    /* Start to Create Command to Write into Suprema Fingerprint */
            command[0] = START;
            command[1] = ET;
            command[2] = char (adr & 0xff);
            command[3] = char (adr/256 & 0xff);
            command[4] = char (adr/65536 & 0xff);
            command[5] = char (adr/16777216 & 0xff);
            command[6] = size[1];
            command[7] = size[0];
            command[8] = size[2];
            command[9] = size[3];
            command[10] = ADD_NEW;
            command[11] = calc_checksum_D (command,12);
            command[12] = END;
    /* End of Creating Command to Write into Suprema Fingerprint */
        *databuf1 = QByteArray((char*)command, 13);
        *databuf2 = *databuf1 + temp;
        *test = databuf2->toHex();
            qDebug() << *test;
        WriteM(*test);
        delete test;
        delete size_temp;
        delete temp2;
        delete databuf1;
        delete databuf2;
        mutex.unlock();
        return 1;
    } catch (...) {
        delete test;
        delete size_temp;
        delete temp2;
        delete databuf1;
        delete databuf2;
        mutex.unlock();
        return 1;
    }
}

int DriverFinger::Delete_template(long int adr)
{

    if (!serialme1->open(QIODevice::ReadWrite))
        serialme1->open(QIODevice::ReadWrite);
    int *temp = new int;
    *temp = adr;
    *temp = *temp & (short)0xff00;
    *temp = *temp >> 8;
    addr[0] = (char) *temp;
    addr[1] = (char) ((short) 0xff & adr);
    addr[2] = 0x00;
    addr[3] = 0x00;
/* Start to Create Command to Write into Suprema Fingerprint */
        command[0] = START;
        command[1] = DT;
        command[2] = char (adr & 0xff);
        command[3] = char (adr/256 & 0xff);
        command[4] = char (adr/65536 & 0xff);
        command[5] = char (adr/16777216 & 0xff);
        command[6] = 0x00;
        command[7] = 0x00;
        command[8] = 0x00;
        command[9] = 0x00;
        command[10] = 0x00;
        command[11] = calc_checksum_D (command,12);
        command[12] = END;
/* End of Creating Command to Write into Suprema Fingerprint */
    QByteArray *databuf1 = new QByteArray;
    *databuf1 = QByteArray((char*)command, 13);
    QString *test = new QString;
    *test = databuf1->toHex();
    WriteM(*test);

    delete test;
    delete databuf1;
    delete temp;

    return 1;
}


void DriverFinger::recieve()
{
    if (DeviceIsNotActive == false)
    {
        *responseData += serialme1->readAll();

        while (serialme1->waitForReadyRead(10))
            *responseData += serialme1->readAll();
        QByteArray dd = *responseData;
        readS = responseData->toHex();
        *inputCase = readS.mid(2,2);
    /************************************************************************************/
    /*                             Identify FingerPrint                                 */
    /************************************************************************************/
        if (*inputCase == ISstring)
        {
            *inputCase = readS.mid(20,2);
            if(*inputCase == SCAN_SUCCESSstring)
            {
                responseData->clear();
            }
            else if(*inputCase != SCAN_SUCCESSstring && *inputCase == SUCCESSstring)
            {
                QString *EmpNo_Finger_String = new QString;
                *EmpNo_Finger_String = "";
                QString *EmpNo_Finger_String_Temp = new QString;
                *EmpNo_Finger_String = *EmpNo_Finger_String + readS[5] + readS[4] + readS[7] + readS[6] + readS[9] + readS[8] + readS[11] + readS[10];
                bool *ok = new bool;
                int *EmpNo_Finger_Int = new int;
                *EmpNo_Finger_Int = 0;
                for (int i=0;i<8;i++)
                {
                   *EmpNo_Finger_String_Temp = EmpNo_Finger_String->at(i);
                   *EmpNo_Finger_Int = *EmpNo_Finger_Int + EmpNo_Finger_String_Temp->toInt(ok,16) * pow(16,i);
                }
                InsertIntoDatafile(*EmpNo_Finger_Int);
                responseData->clear();
                delete ok;
                delete EmpNo_Finger_Int;
            }
            else if (*inputCase != SCAN_SUCCESSstring && *inputCase == NOT_FOUNDstring)
            {                
                responseData->clear();
                GetPolicy(-1);
                emit identify(tr("Not Defined"),"",0,0,"0");
            }
            else
            {
                qDebug() << "Try Again";
            }
        }
    /************************************************************************************/
    /*                             Read Template FingerPrint                            */
    /************************************************************************************/
        else if (*inputCase == RTstring) {
            *inputCase = readS.mid(20,2);
            if(*inputCase == SUCCESSstring)
            {
                QByteArray ss = readS.right(readS.length() - 26).toUtf8();
                FingerPrintTemplateByteArray.clear();
                responseData->remove(0,13);
                responseData->remove(responseData->length()-1,1);
                FingerPrintTemplateByteArray.append(*responseData);
                _loop.exit();
                responseData->clear();
                EnrollFlag = false;
            }
            else if(*inputCase == NOT_FOUNDstring)
            {
                FingerPrintTemplate.clear();
                responseData->clear();
                EnrollFlag = false;
                _loop.exit();
            }
            else if(*inputCase == CONTINUEstring)
            {
                int *iterationforFingerTemplate = new int;
                *iterationforFingerTemplate = responseData->length() / 398;
                while (*iterationforFingerTemplate > 0) {
                    --*iterationforFingerTemplate;
                    FingerPrintTemplateByteArray.append(responseData->mid(13,384));
                    responseData->remove(0,398);
                }
                responseData->clear();
                EnrollFlag = false;
                delete iterationforFingerTemplate;
                _loop.exit();
            }
            else
                responseData->clear();
            if (mutex.isRecursive())
                mutex.lock();
            else
                mutex.unlock();
        }
    /************************************************************************************/
    /*                      Check User ID Number of Template                            */
    /***************************************InsertIntoDatafile***************************/
        else if (*inputCase == CTstring) {
            *inputCase = readS.mid(20,2);
            if(*inputCase == EXIST_IDstring)
            {
                NumbersOfTemplate = ArrayHextoInt(responseData->mid(6,4));
                responseData->clear();
                EnrollFlag = false;
            }
            else
            {
                NumbersOfTemplate = 0;
                responseData->clear();
                EnrollFlag = false;
            }
        }
    /************************************************************************************/
    /*                    Enroll Template FingerPrint by Template                       */
    /************************************************************************************/
        else if (*inputCase == ETstring) {
            responseData->clear();
            EnrollFlag = false;
        }
    /************************************************************************************/
    /*                    Enroll Template FingerPrint by Scan                           */
    /************************************************************************************/
        else if (*inputCase == ESstring) {
            *inputCase = readS.mid(20,2);
            if(*inputCase == SCAN_SUCCESSstring)
            {
                responseData->clear();
            }
            else if (*inputCase != SCAN_SUCCESSstring && *inputCase == TIME_OUTstring)     // Time Out during to enroll fingerprint
            {
                responseData->clear();
                emit sendAckofEnroll(tr("Unsuccessful!"),2);
                EnrollFlag = false;
            }
            else if (*inputCase != SCAN_SUCCESSstring && *inputCase == SUCCESSstring)     // Enroll first Step
            {
                responseData->clear();
                if (EnrollFlag)
                {
                    emit sendAckofEnroll(tr("Saved"),2);
                    EnrollFlag = false;
                }
                else
                {
                    emit sendAckofEnroll(tr("Try again"),1);
                    EnrollFlag = true;
                }
            }
            else if (*inputCase != SCAN_SUCCESSstring && *inputCase == MEM_FULLstring) {
                responseData->clear();
                qDebug() << "DSP memory is full";
            }
            else if (*inputCase != SCAN_SUCCESSstring && *inputCase == FINGER_LIMITstring) {
                responseData->clear();
                qDebug() << "Finger Limit";
            }
            else if (*inputCase != SCAN_SUCCESSstring && *inputCase == EXIST_FINGERstring) {
                responseData->clear();
                qDebug() << "Finger is Exist";
            }
            else if (*inputCase != SCAN_SUCCESSstring && *inputCase == NOT_MATCHstring) {
                responseData->clear();
                qDebug() << "Finger not match 2 step";
            }
            else {
                responseData->clear();
            }
        }
    /************************************************************************************/
    /*                             Delete All Template                                  */
    /************************************************************************************/
        else if (*inputCase == DAstring) {
            responseData->clear();
            EnrollFlag = false;
        }
    /************************************************************************************/
    /*                             Delete User Template                                 */
    /************************************************************************************/
        else if (*inputCase == DTstring) {
            responseData->clear();
            EnrollFlag = false;
        }

    /*************************************************************************************/
    /*                      Check Number of Enrolled FingerPrint Template                */
    /*************************************************************************************/
        else if (*inputCase == SRstring) {
            *inputCase = readS.mid(20,2);
            if(*inputCase == SUCCESSstring)
            {
                NumbersOfTemplate = (((static_cast<unsigned int>(responseData->at(6)) & 0xFF) * (1))
                        + ((static_cast<unsigned int>(responseData->at(7)) & 0xFF) * (256))
                        + ((static_cast<unsigned int>(responseData->at(8)) & 0xFF) * (16777216))
                        + ((static_cast<unsigned int>(responseData->at(9)) & 0xFF) * (65536)));
                                qDebug() << NumbersOfTemplate;
                responseData->clear();
                _loop.exit();
            }
            else                                                                                      
            {
                NumbersOfTemplate = -1;
                responseData->clear();
            }
        }
    /************************************************************************************/
    /*                                      ELSE!                                       */
    /************************************************************************************/
        else {
            responseData->clear();
            EnrollFlag = false;
        }
    }
}

void DriverFinger::quitLoop()
{
    NumbersOfTemplate = -1;
    timer.stop();
    _loop.exit();
}


int DriverFinger::ArrayHextoInt(QByteArray HexStream)
{
    return (((static_cast<unsigned int>(HexStream[0]) & 0xFF) * (1))
            + ((static_cast<unsigned int>(HexStream[1]) & 0xFF) * (256))
            + ((static_cast<unsigned int>(HexStream[2]) & 0xFF) * (16777216))
            + ((static_cast<unsigned int>(HexStream[3]) & 0xFF) * (65536)));
}

DriverFinger* DriverFinger::GetInstance()
{
    if (!_instance)
        _instance = new DriverFinger();
    return _instance;
}



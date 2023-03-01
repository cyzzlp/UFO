#include "DataSortThread.h"
#include "MarkData.h"
#include "GlobalInfo.h"

DataSortThread::DataSortThread(QObject *parent)
	: QThread(parent)
{

}

DataSortThread::~DataSortThread()
{

}

void DataSortThread::run()
{
    // ��ȡ�����ļ���ַ�����Ե�ַ��
    QString m_FileName = QCoreApplication::applicationDirPath() + "/gapSetting.ini";
    gap = new QSettings(m_FileName, QSettings::IniFormat);

    // ��ȡԤ����
    xGap = gap->value("xGap").toDouble();
    yGap = gap->value("yGap").toDouble();
    DataType = gap->value("dataType").toBool();

    FileName = GlobalInfo::aFileName;

    // Ĭ��ΪXY����
    IsErrorTextColumns = 2;

    emit setTextToLabel("��ȡ��");

    // �ı���ȡ
    QFile afile(FileName);
    afile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textstream(&afile);

    // �ж������޴����
    if (!DataType)
        IsErrorTextColumns = 3;

    // ��ֵ
    int returnValue = 0;

    // �ݴ��ı�����ֵ
    double data = 0;

    // ��ȡ�ļ�����
    while (!textstream.atEnd())
    {
        QString str = textstream.readLine();
        QStringList strList = str.split(",");
        QListIterator<QString> MarkTextData(strList);
        MarkTextColumns = strList.size();

        // ����ʾ��������
        if (MarkTextColumns != IsErrorTextColumns)
        {
            emit DelieveWrongInfo("�ļ�����ά�Ȳ�һ��");
            return;
        }

        // ��ʼ�������Ĺ�ģ
        MarkData::returnMarkData.resize(returnValue + 1);
        MarkData::returnMarkData[returnValue].resize(3);

        // ���ݵ�������
        for (int j = 0; j < MarkTextColumns; ++j)
        {
            data = MarkTextData.next().toDouble();
            MarkData::returnMarkData[returnValue][j] = data;
        }
        // ��ȡ��һ��
        ++returnValue;
    }

    // �ر��ı�
    afile.close();

    // ��¼�ı�������
    GlobalInfo::MarkTextRows = returnValue;
    GlobalInfo::MarkTextColumns = IsErrorTextColumns;

    emit setTextToLabel("������");

    // ��������
    int m_dataType = 0;

    // ���������ֵ
    int m_count = 0;

    // ��ʼ�����ݱ�ǩ����
    for (int i = 0; i < returnValue - 1; ++i)
    {
        double x_gap = MarkData::returnMarkData[i + 1][0] - MarkData::returnMarkData[i][0];
        double y_gap = MarkData::returnMarkData[i + 1][1] - MarkData::returnMarkData[i][1];
        double z1 = MarkData::returnMarkData[i][2];
        double z2 = MarkData::returnMarkData[i + 1][2];

        MarkData::MarkTextDataType.resize(m_dataType + 1);
        MarkData::MarkTextDataType[m_dataType].resize(3);

        // ͬ������
        if ((abs(x_gap) > xGap) || (abs(y_gap) > yGap) && (z1 == z2))
        {
            MarkData::MarkTextDataType[m_dataType][0] = m_count;
            MarkData::MarkTextDataType[m_dataType][1] = i;
            MarkData::MarkTextDataType[m_dataType][2] = 0;
            ++m_dataType;
            m_count = i + 2;
        }

        // ��ͬ��
        if ((z1 != z2))
        {

            MarkData::MarkTextDataType[m_dataType][0] = m_count;
            MarkData::MarkTextDataType[m_dataType][1] = i;
            MarkData::MarkTextDataType[m_dataType][2] = 1;
            ++m_dataType;
            m_count = i + 2;
        }
    }

    // �����
    if (m_count != returnValue)
    {
        MarkData::MarkTextDataType.resize(m_dataType + 1);
        MarkData::MarkTextDataType[m_dataType].resize(3);

        MarkData::MarkTextDataType[m_dataType][0] = m_count;
        MarkData::MarkTextDataType[m_dataType][1] = returnValue - 1;
        MarkData::MarkTextDataType[m_dataType][2] = 0;
    }
   
    emit MarkDataNum(returnValue);

    // ���ݴ����������
    emit setTextToLabel("���");
}

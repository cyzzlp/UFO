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
    // 获取配置文件地址（绝对地址）
    QString m_FileName = QCoreApplication::applicationDirPath() + "/gapSetting.ini";
    gap = new QSettings(m_FileName, QSettings::IniFormat);

    // 读取预设间隔
    xGap = gap->value("xGap").toDouble();
    yGap = gap->value("yGap").toDouble();
    DataType = gap->value("dataType").toBool();

    FileName = GlobalInfo::aFileName;

    // 默认为XY数据
    IsErrorTextColumns = 2;

    emit setTextToLabel("读取中");

    // 文本读取
    QFile afile(FileName);
    afile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textstream(&afile);

    // 判断数据无错误点
    if (!DataType)
        IsErrorTextColumns = 3;

    // 行值
    int returnValue = 0;

    // 暂存文本数据值
    double data = 0;

    // 读取文件数据
    while (!textstream.atEnd())
    {
        QString str = textstream.readLine();
        QStringList strList = str.split(",");
        QListIterator<QString> MarkTextData(strList);
        MarkTextColumns = strList.size();

        // 若提示数据有误
        if (MarkTextColumns != IsErrorTextColumns)
        {
            emit DelieveWrongInfo("文件数据维度不一致");
            return;
        }

        // 初始化向量的规模
        MarkData::returnMarkData.resize(returnValue + 1);
        MarkData::returnMarkData[returnValue].resize(3);

        // 数据导入向量
        for (int j = 0; j < MarkTextColumns; ++j)
        {
            data = MarkTextData.next().toDouble();
            MarkData::returnMarkData[returnValue][j] = data;
        }
        // 获取下一行
        ++returnValue;
    }

    // 关闭文本
    afile.close();

    // 记录文本行列数
    GlobalInfo::MarkTextRows = returnValue;
    GlobalInfo::MarkTextColumns = IsErrorTextColumns;

    emit setTextToLabel("分类中");

    // 数据类型
    int m_dataType = 0;

    // 标刻左区间值
    int m_count = 0;

    // 初始化数据标签向量
    for (int i = 0; i < returnValue - 1; ++i)
    {
        double x_gap = MarkData::returnMarkData[i + 1][0] - MarkData::returnMarkData[i][0];
        double y_gap = MarkData::returnMarkData[i + 1][1] - MarkData::returnMarkData[i][1];
        double z1 = MarkData::returnMarkData[i][2];
        double z2 = MarkData::returnMarkData[i + 1][2];

        MarkData::MarkTextDataType.resize(m_dataType + 1);
        MarkData::MarkTextDataType[m_dataType].resize(3);

        // 同面跳点
        if ((abs(x_gap) > xGap) || (abs(y_gap) > yGap) && (z1 == z2))
        {
            MarkData::MarkTextDataType[m_dataType][0] = m_count;
            MarkData::MarkTextDataType[m_dataType][1] = i;
            MarkData::MarkTextDataType[m_dataType][2] = 0;
            ++m_dataType;
            m_count = i + 2;
        }

        // 非同面
        if ((z1 != z2))
        {

            MarkData::MarkTextDataType[m_dataType][0] = m_count;
            MarkData::MarkTextDataType[m_dataType][1] = i;
            MarkData::MarkTextDataType[m_dataType][2] = 1;
            ++m_dataType;
            m_count = i + 2;
        }
    }

    // 标刻完
    if (m_count != returnValue)
    {
        MarkData::MarkTextDataType.resize(m_dataType + 1);
        MarkData::MarkTextDataType[m_dataType].resize(3);

        MarkData::MarkTextDataType[m_dataType][0] = m_count;
        MarkData::MarkTextDataType[m_dataType][1] = returnValue - 1;
        MarkData::MarkTextDataType[m_dataType][2] = 0;
    }
   
    emit MarkDataNum(returnValue);

    // 传递处理完的数据
    emit setTextToLabel("完成");
}

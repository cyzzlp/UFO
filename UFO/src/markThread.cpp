#include "markThread.h"

markThread::markThread(QObject *parent)
	: QObject(parent)
{
	// 相机句柄
	ID = GlobalInfo::ID;
	szAxes[0] = GlobalInfo::szAxes[0];

	m_running = false;
}

markThread::~markThread()
{

}

// 线程启动
void markThread::Start()
{
	// 标刻文件行数
	int fileRows = GlobalInfo::MarkTextRows;

	// 标刻文件列数
	int fileColumns = GlobalInfo::MarkTextColumns;

	// 组数
	int groupSize = MarkData::MarkTextDataType.size();

	// 开始标刻
	m_running = true;

	// 记录目前标刻的组别
	int groupCount = 0;

	while (m_running)
	{
		count = MarkData::MarkTextDataType[groupCount][0];
		m_count = MarkData::MarkTextDataType[groupCount][1];
		labels = MarkData::MarkTextDataType[groupCount][2];

		if (labels == 0)
		{
			// 标刻数据长度
			int Rows = m_count - count + 1;

			// x坐标标刻数组
			xMarkData = new double[Rows]();

			// y坐标标刻数组
			yMarkData = new double[Rows]();

			// 读取标刻数据
			for (int i = 0; i < Rows; i++)
			{
				xMarkData[i] = MarkData::returnMarkData[count + i][0];
				yMarkData[i] = MarkData::returnMarkData[count + i][1];
			}

			// 准备标刻阶段
			ReadyMark();

			// 启动打标线程
			StartReadDataThread();

			// 设置标刻次数
			SetOverallMarkCounts(GlobalInfo::MarkCount);

			// 清零量计数器数据
			ZeroCounter();

			// 矢量命令分解函数
			MarkCommand_Vector(Rows, xMarkData, yMarkData);

			// 结束命令
			EndCommand();

			// 通知算数据结束
			WriteDataEnd();

			while (GetMarkStatus())
			{
				// 等待20毫秒
				QThread::msleep(30);

				// 获取振镜位置
				GetScannerPosition(xPos, yPos);

				// 发送振镜位置信号
				emit MarkRealPos(xPos, yPos);
			}
		}

		if (labels == 1)
		{
			// 标刻数据长度
			int Rows = m_count - count;

			// x坐标标刻数组
			xMarkData = new double[Rows]();

			// y坐标标刻数组
			yMarkData = new double[Rows]();

			// 下层位置
			zPos = MarkData::returnMarkData[m_count + 1][2];

			// 读取标刻数据
			for (int i = 0; i < Rows; i++)
			{
				xMarkData[i] = MarkData::returnMarkData[count + i][0];
				yMarkData[i] = MarkData::returnMarkData[count + i][1];
			}

			// 准备标刻阶段
			ReadyMark();

			// 启动打标线程
			StartReadDataThread();

			// 设置标刻次数
			SetOverallMarkCounts(GlobalInfo::MarkCount);

			// 清零量计数器数据
			ZeroCounter();

			// 矢量命令分解函数
			MarkCommand_Vector(Rows, xMarkData, yMarkData);

			// 跳转
			JumpCommand(x_jump, y_jump);

			// 结束命令
			EndCommand();

			// 通知算数据结束
			WriteDataEnd();

			while (GetMarkStatus())
			{
				// 等待20毫秒
				QThread::msleep(30);

				// 获取振镜位置
				GetScannerPosition(xPos, yPos);

				// 发送振镜位置信号
				emit MarkRealPos(xPos, yPos);
			}

			dPos[0] = zPos + GlobalInfo::presentSetZero;

			 // 换层(移动z轴位置)
			returnValue = PI_MOV(ID, szAxes, dPos);
			if (!returnValue)
			{
				iError = PI_GetError(ID);
				PI_TranslateError(iError, szErrorMesage, 1024);
				emit EmitWrongInfo(szErrorMesage);
				PI_CloseConnection(ID);
				return;
			}
			// 选择等待轴
			bIsMoving[0] = TRUE;
			while (bIsMoving[0] == TRUE)
			{
				returnValue = PI_qPOS(ID, szAxes, dPos);
				// 获得连接轴的位置
				if (!returnValue)
				{
					iError = PI_GetError(ID);
					PI_TranslateError(iError, szErrorMesage, 1024);					
					emit EmitWrongInfo(szErrorMesage);
					PI_CloseConnection(ID);
					return;
				}

				returnValue = PI_IsMoving(ID, NULL, bIsMoving);
				if (!returnValue)
				{
					iError = PI_GetError(ID);
					PI_TranslateError(iError, szErrorMesage, 1024);
					emit EmitWrongInfo(szErrorMesage);
					PI_CloseConnection(ID);
					return;
				}
			}
		}

		// 释放动态内存
		delete[]xMarkData;
		delete[]yMarkData;

		// 标刻下一组
		groupCount = groupCount + 1;

		if (groupCount == groupSize)
		{
			Stop();
			GlobalInfo::mthread = false;
			break;
		}		
	}
}

// 线程停止
void markThread::Stop()
{
	// 停止数据分解
	m_running = false;
}
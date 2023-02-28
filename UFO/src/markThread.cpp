#include "markThread.h"

markThread::markThread(QObject *parent)
	: QObject(parent)
{
	// 相机句柄
	ID = GlobalInfo::ID;
	szAxes[0] = GlobalInfo::szAxes[0];
	szAxes[1] = GlobalInfo::szAxes[1];

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

	// 标刻起点
	int count{};

	// 标刻终点
	int m_count{};

	// 记录上次标刻起点
	int counts{};

	// 记录上次标刻终点
	int m_counts{};

	// 标刻类型
	int labels{};

	// 开始标刻
	m_running = true;

	while (m_running)
	{
		// 记录目前标刻的组别
		int i = 0;

		count = MarkData::MarkTextDataType[i][0];
		m_count = MarkData::MarkTextDataType[i][1];
		labels = MarkData::MarkTextDataType[i][2];

		// 第一组是完整的，其余的都会因为跳转或者换面少一个点
		if (labels == 1 && counts == 0)
		{
			// 标刻数据长度
			int Rows = m_count - count + 1;

			// x坐标标刻数组
			xMarkData = new double[Rows]();

			// y坐标标刻数组
			yMarkData = new double[Rows]();

			// 读取标刻数据
			for (count; count < m_count; count++)
			{
				xMarkData[count] = MarkData::returnMarkData[count][0];
				yMarkData[count] = MarkData::returnMarkData[count][1];
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

			QThread::msleep(100);

			bool isMark = true;

			while (isMark)
			{
				// 获取振镜位置
				GetScannerPosition(xPos, yPos);

				// 等待20毫秒
				QThread::msleep(20);

				// 发送振镜位置信号
				emit MarkRealPos(xPos, yPos);

				// 读取当前振镜标刻状态
				isMark = GetMarkStatus();
			}
		}

		// 下个面为跳点
		if (labels == 1)
		{
			// 标刻数据长度
			int Rows = m_count - count;

			// x坐标标刻数组
			xMarkData = new double[Rows]();

			// y坐标标刻数组
			yMarkData = new double[Rows]();

			// 读取标刻数据
			for (count; count < m_count; count++)
			{
				xMarkData[count] = MarkData::returnMarkData[count][0];
				yMarkData[count] = MarkData::returnMarkData[count][1];
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

			QThread::msleep(100);

			bool isMark = true;

			while (isMark)
			{
				// 获取振镜位置
				GetScannerPosition(xPos, yPos);

				// 等待20毫秒
				QThread::msleep(20);

				// 发送振镜位置信号
				emit MarkRealPos(xPos, yPos);

				// 读取当前振镜标刻状态
				isMark = GetMarkStatus();
			}                                                                                                      
		}

		if (labels == 2)
		{
			// 标刻数据长度
			int Rows = m_count - count;

			// x坐标标刻数组
			xMarkData = new double[Rows]();

			// y坐标标刻数组
			yMarkData = new double[Rows]();

			// 下层位置
			zPos = MarkData::returnMarkData[m_counts + 1][2];

			if (counts < m_counts)
			{
				for (count; count <= m_count; count++)
				{
					xMarkData[count] = MarkData::returnMarkData[count][0];
					yMarkData[count] = MarkData::returnMarkData[count][1];
				}
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

			QThread::msleep(50);

			bool isMark = true;

			while (isMark)
			{
				// 获取振镜位置
				GetScannerPosition(xPos, yPos);

				// 等待20毫秒
				QThread::msleep(20);

				// 发送振镜位置信号
				emit MarkRealPos(xPos, yPos);

				// 读取当前振镜标刻状态
				isMark = GetMarkStatus();
			}

			dPos[0] = zPos + GlobalInfo::presentSetZero;

			// 换面
			returnValue = PI_MOV(ID, szAxes, dPos);
			if (!returnValue)
			{
				char error[1024];
				iError = PI_GetError(ID);
				PI_TranslateError(iError, szErrorMesage, 1024);
				strcpy(error, szErrorMesage);
				QMessageBox::critical(nullptr, "PI", szErrorMesage);
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
					char error[1024];
					iError = PI_GetError(ID);
					PI_TranslateError(iError, szErrorMesage, 1024);
					strcpy(error, szErrorMesage);
					PI_CloseConnection(ID);
					QMessageBox::critical(nullptr, "PI", szErrorMesage);
					return;
				}

				returnValue = PI_IsMoving(ID, NULL, bIsMoving);
				if (!returnValue)
				{
					char error[1024];
					iError = PI_GetError(ID);
					PI_TranslateError(iError, szErrorMesage, 1024);
					strcpy(error, szErrorMesage);
					QMessageBox::critical(nullptr, "PI", szErrorMesage);
					PI_CloseConnection(ID);
					return;
				}
			}
		}

		// 释放动态内存
		delete[]xMarkData;
		delete[]yMarkData;
	}
}

// 线程停止
void markThread::Stop()
{

}
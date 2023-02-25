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
	for (int i = 0; i < MarkData::MarkTextDataType.size(); i++)
	{
		count = MarkData::MarkTextDataType[i][0];
		m_count = MarkData::MarkTextDataType[i][1];
		labels = MarkData::MarkTextDataType[i][2];

		counts = count;
		m_counts = m_count;

		// 启动标志
		m_running = true;

		if (labels == 0)
		{
			// x坐标标刻数组
			xMarkData = new double[m_counts - counts]();

			// y坐标标刻数组
			yMarkData = new double[m_counts - counts]();

			if (counts < m_counts)
			{
				for (count; count < m_count; ++count)
				{
					xMarkData[count] = MarkData::returnMarkData[count] [0] ;
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
			MarkCommand_Vector((m_counts - counts), xMarkData, yMarkData);

			// 结束命令
			EndCommand();

			// 通知算数据结束
			WriteDataEnd();

			QThread::msleep(100);

			while (m_running)
			{
				// 延时
				QThread::msleep(20);

				// 获取振镜位置
				GetScannerPosition(xpos, ypos);

				// 发送位置信号
				emit MarkRealPos(xpos, ypos);
			}
		}

		if (labels == 1 && counts == 0)
		{
			// x坐标标刻数组
			xMarkData = new double[m_counts - counts + 1]();

			// y坐标标刻数组
			yMarkData = new double[m_counts - counts + 1]();

			// 获取跳点
			x_jump = MarkData::returnMarkData[m_counts + 1][0];
			y_jump = MarkData::returnMarkData[m_counts + 1][1];

			if (counts < m_counts)
			{
				for (count; count < m_count; ++count)
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
			MarkCommand_Vector((m_counts - counts + 1), xMarkData, yMarkData);

			// 结束命令
			EndCommand();

			// 通知算数据结束
			WriteDataEnd();

			QThread::msleep(100);

			while (m_running)
			{
				// 延时
				QThread::msleep(20);

				// 获取振镜位置
				GetScannerPosition(xpos, ypos);

				// 发送位置信号
				emit MarkRealPos(xpos, ypos);
			}
		}

		if (labels == 1 && counts != 0)
		{
			// x坐标标刻数组
			xMarkData = new double[m_counts - counts]();

			// y坐标标刻数组
			yMarkData = new double[m_counts - counts]();

			// 获取跳点
			x_jump = MarkData::returnMarkData[m_counts + 1][0];
			y_jump = MarkData::returnMarkData[m_counts + 1][1];

			if (counts < m_counts)
			{
				for (count; count < m_count; ++count)
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
			MarkCommand_Vector((m_counts - counts), xMarkData, yMarkData);

			// 跳转
			JumpCommand(x_jump, y_jump);

			// 结束命令
			EndCommand();

			// 通知算数据结束
			WriteDataEnd();

			QThread::msleep(100);

			while (m_running)
			{
				// 延时
				QThread::msleep(20);

				// 获取振镜位置
				GetScannerPosition(xpos, ypos);

				// 发送位置信号
				emit MarkRealPos(xpos, ypos);
			}
		}

		if (labels == 2)
		{
			// x坐标标刻数组
			xMarkData = new double[m_counts - counts]();

			// y坐标标刻数组
			yMarkData = new double[m_counts - counts]();

			// 下层位置
			zpos = MarkData::returnMarkData[m_counts + 1][2];

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
			MarkCommand_Vector((m_counts - counts), xMarkData, yMarkData);

			// 跳转
			JumpCommand(x_jump, y_jump);

			// 结束命令
			EndCommand();

			// 通知算数据结束
			WriteDataEnd();

			QThread::msleep(50);

			while (m_running)
			{
				// 延时
				QThread::msleep(20);

				// 获取振镜位置
				GetScannerPosition(xpos, ypos);

				// 发送位置信号
				emit MarkRealPos(xpos, ypos);
			}

			dPos[0] = zpos + GlobalInfo::presentSetZero;

			// 换面
			BOOL returnValue = PI_MOV(ID, szAxes, dPos);
			if (!returnValue)
			{
				iError = PI_GetError(ID);
				PI_TranslateError(iError, szErrorMesage, 1024);
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
					iError = PI_GetError(ID);
					PI_TranslateError(iError, szErrorMesage, 1024);
					PI_CloseConnection(ID);
					QMessageBox::critical(nullptr, "PI", szErrorMesage);
					return;
				}

				returnValue = PI_IsMoving(ID, NULL, bIsMoving);
				if (!returnValue)
				{
					iError = PI_GetError(ID);
					PI_TranslateError(iError, szErrorMesage, 1024);
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
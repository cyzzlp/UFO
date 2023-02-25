#include "markThread.h"

markThread::markThread(QObject *parent)
	: QObject(parent)
{
	// ������
	ID = GlobalInfo::ID;
	szAxes[0] = GlobalInfo::szAxes[0];
	szAxes[1] = GlobalInfo::szAxes[1];

	m_running = false;
}

markThread::~markThread()
{

}

// �߳�����
void markThread::Start()
{
	for (int i = 0; i < MarkData::MarkTextDataType.size(); i++)
	{
		count = MarkData::MarkTextDataType[i][0];
		m_count = MarkData::MarkTextDataType[i][1];
		labels = MarkData::MarkTextDataType[i][2];

		counts = count;
		m_counts = m_count;

		// ������־
		m_running = true;

		if (labels == 0)
		{
			// x����������
			xMarkData = new double[m_counts - counts]();

			// y����������
			yMarkData = new double[m_counts - counts]();

			if (counts < m_counts)
			{
				for (count; count < m_count; ++count)
				{
					xMarkData[count] = MarkData::returnMarkData[count] [0] ;
					yMarkData[count] = MarkData::returnMarkData[count][1];
				}
			}

			// ׼����̽׶�
			ReadyMark();

			// ��������߳�
			StartReadDataThread();

			// ���ñ�̴���
			SetOverallMarkCounts(GlobalInfo::MarkCount);

			// ����������������
			ZeroCounter();

			// ʸ������ֽ⺯��
			MarkCommand_Vector((m_counts - counts), xMarkData, yMarkData);

			// ��������
			EndCommand();

			// ֪ͨ�����ݽ���
			WriteDataEnd();

			QThread::msleep(100);

			while (m_running)
			{
				// ��ʱ
				QThread::msleep(20);

				// ��ȡ��λ��
				GetScannerPosition(xpos, ypos);

				// ����λ���ź�
				emit MarkRealPos(xpos, ypos);
			}
		}

		if (labels == 1 && counts == 0)
		{
			// x����������
			xMarkData = new double[m_counts - counts + 1]();

			// y����������
			yMarkData = new double[m_counts - counts + 1]();

			// ��ȡ����
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

			// ׼����̽׶�
			ReadyMark();

			// ��������߳�
			StartReadDataThread();

			// ���ñ�̴���
			SetOverallMarkCounts(GlobalInfo::MarkCount);

			// ����������������
			ZeroCounter();

			// ʸ������ֽ⺯��
			MarkCommand_Vector((m_counts - counts + 1), xMarkData, yMarkData);

			// ��������
			EndCommand();

			// ֪ͨ�����ݽ���
			WriteDataEnd();

			QThread::msleep(100);

			while (m_running)
			{
				// ��ʱ
				QThread::msleep(20);

				// ��ȡ��λ��
				GetScannerPosition(xpos, ypos);

				// ����λ���ź�
				emit MarkRealPos(xpos, ypos);
			}
		}

		if (labels == 1 && counts != 0)
		{
			// x����������
			xMarkData = new double[m_counts - counts]();

			// y����������
			yMarkData = new double[m_counts - counts]();

			// ��ȡ����
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

			// ׼����̽׶�
			ReadyMark();

			// ��������߳�
			StartReadDataThread();

			// ���ñ�̴���
			SetOverallMarkCounts(GlobalInfo::MarkCount);

			// ����������������
			ZeroCounter();

			// ʸ������ֽ⺯��
			MarkCommand_Vector((m_counts - counts), xMarkData, yMarkData);

			// ��ת
			JumpCommand(x_jump, y_jump);

			// ��������
			EndCommand();

			// ֪ͨ�����ݽ���
			WriteDataEnd();

			QThread::msleep(100);

			while (m_running)
			{
				// ��ʱ
				QThread::msleep(20);

				// ��ȡ��λ��
				GetScannerPosition(xpos, ypos);

				// ����λ���ź�
				emit MarkRealPos(xpos, ypos);
			}
		}

		if (labels == 2)
		{
			// x����������
			xMarkData = new double[m_counts - counts]();

			// y����������
			yMarkData = new double[m_counts - counts]();

			// �²�λ��
			zpos = MarkData::returnMarkData[m_counts + 1][2];

			if (counts < m_counts)
			{
				for (count; count <= m_count; count++)
				{
					xMarkData[count] = MarkData::returnMarkData[count][0];
					yMarkData[count] = MarkData::returnMarkData[count][1];
				}
			}

			// ׼����̽׶�
			ReadyMark();

			// ��������߳�
			StartReadDataThread();

			// ���ñ�̴���
			SetOverallMarkCounts(GlobalInfo::MarkCount);

			// ����������������
			ZeroCounter();

			// ʸ������ֽ⺯��
			MarkCommand_Vector((m_counts - counts), xMarkData, yMarkData);

			// ��ת
			JumpCommand(x_jump, y_jump);

			// ��������
			EndCommand();

			// ֪ͨ�����ݽ���
			WriteDataEnd();

			QThread::msleep(50);

			while (m_running)
			{
				// ��ʱ
				QThread::msleep(20);

				// ��ȡ��λ��
				GetScannerPosition(xpos, ypos);

				// ����λ���ź�
				emit MarkRealPos(xpos, ypos);
			}

			dPos[0] = zpos + GlobalInfo::presentSetZero;

			// ����
			BOOL returnValue = PI_MOV(ID, szAxes, dPos);
			if (!returnValue)
			{
				iError = PI_GetError(ID);
				PI_TranslateError(iError, szErrorMesage, 1024);
				QMessageBox::critical(nullptr, "PI", szErrorMesage);
				PI_CloseConnection(ID);
				return;
			}
			// ѡ��ȴ���
			bIsMoving[0] = TRUE;
			while (bIsMoving[0] == TRUE)
			{
				returnValue = PI_qPOS(ID, szAxes, dPos);
				// ����������λ��
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

		// �ͷŶ�̬�ڴ�
		delete[]xMarkData;
		delete[]yMarkData;
	}
}

// �߳�ֹͣ
void markThread::Stop()
{

}
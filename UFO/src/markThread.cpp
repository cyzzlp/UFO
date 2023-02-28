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
	// ����ļ�����
	int fileRows = GlobalInfo::MarkTextRows;

	// ����ļ�����
	int fileColumns = GlobalInfo::MarkTextColumns;

	// ������
	int count{};

	// ����յ�
	int m_count{};

	// ��¼�ϴα�����
	int counts{};

	// ��¼�ϴα���յ�
	int m_counts{};

	// �������
	int labels{};

	// ��ʼ���
	m_running = true;

	while (m_running)
	{
		// ��¼Ŀǰ��̵����
		int i = 0;

		count = MarkData::MarkTextDataType[i][0];
		m_count = MarkData::MarkTextDataType[i][1];
		labels = MarkData::MarkTextDataType[i][2];

		// ��һ���������ģ�����Ķ�����Ϊ��ת���߻�����һ����
		if (labels == 1 && counts == 0)
		{
			// ������ݳ���
			int Rows = m_count - count + 1;

			// x����������
			xMarkData = new double[Rows]();

			// y����������
			yMarkData = new double[Rows]();

			// ��ȡ�������
			for (count; count < m_count; count++)
			{
				xMarkData[count] = MarkData::returnMarkData[count][0];
				yMarkData[count] = MarkData::returnMarkData[count][1];
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
			MarkCommand_Vector(Rows, xMarkData, yMarkData);

			// ��������
			EndCommand();

			// ֪ͨ�����ݽ���
			WriteDataEnd();

			QThread::msleep(100);

			bool isMark = true;

			while (isMark)
			{
				// ��ȡ��λ��
				GetScannerPosition(xPos, yPos);

				// �ȴ�20����
				QThread::msleep(20);

				// ������λ���ź�
				emit MarkRealPos(xPos, yPos);

				// ��ȡ��ǰ�񾵱��״̬
				isMark = GetMarkStatus();
			}
		}

		// �¸���Ϊ����
		if (labels == 1)
		{
			// ������ݳ���
			int Rows = m_count - count;

			// x����������
			xMarkData = new double[Rows]();

			// y����������
			yMarkData = new double[Rows]();

			// ��ȡ�������
			for (count; count < m_count; count++)
			{
				xMarkData[count] = MarkData::returnMarkData[count][0];
				yMarkData[count] = MarkData::returnMarkData[count][1];
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
			MarkCommand_Vector(Rows, xMarkData, yMarkData);

			// ��������
			EndCommand();

			// ֪ͨ�����ݽ���
			WriteDataEnd();

			QThread::msleep(100);

			bool isMark = true;

			while (isMark)
			{
				// ��ȡ��λ��
				GetScannerPosition(xPos, yPos);

				// �ȴ�20����
				QThread::msleep(20);

				// ������λ���ź�
				emit MarkRealPos(xPos, yPos);

				// ��ȡ��ǰ�񾵱��״̬
				isMark = GetMarkStatus();
			}                                                                                                      
		}

		if (labels == 2)
		{
			// ������ݳ���
			int Rows = m_count - count;

			// x����������
			xMarkData = new double[Rows]();

			// y����������
			yMarkData = new double[Rows]();

			// �²�λ��
			zPos = MarkData::returnMarkData[m_counts + 1][2];

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
			MarkCommand_Vector(Rows, xMarkData, yMarkData);

			// ��ת
			JumpCommand(x_jump, y_jump);

			// ��������
			EndCommand();

			// ֪ͨ�����ݽ���
			WriteDataEnd();

			QThread::msleep(50);

			bool isMark = true;

			while (isMark)
			{
				// ��ȡ��λ��
				GetScannerPosition(xPos, yPos);

				// �ȴ�20����
				QThread::msleep(20);

				// ������λ���ź�
				emit MarkRealPos(xPos, yPos);

				// ��ȡ��ǰ�񾵱��״̬
				isMark = GetMarkStatus();
			}

			dPos[0] = zPos + GlobalInfo::presentSetZero;

			// ����
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
			// ѡ��ȴ���
			bIsMoving[0] = TRUE;
			while (bIsMoving[0] == TRUE)
			{
				returnValue = PI_qPOS(ID, szAxes, dPos);
				// ����������λ��
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

		// �ͷŶ�̬�ڴ�
		delete[]xMarkData;
		delete[]yMarkData;
	}
}

// �߳�ֹͣ
void markThread::Stop()
{

}
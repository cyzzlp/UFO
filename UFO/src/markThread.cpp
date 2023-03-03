#include "markThread.h"

markThread::markThread(QObject *parent)
	: QObject(parent)
{
	// ������
	ID = GlobalInfo::ID;
	szAxes[0] = GlobalInfo::szAxes[0];

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

	// ����
	int groupSize = MarkData::MarkTextDataType.size();

	// ��ʼ���
	m_running = true;

	// ��¼Ŀǰ��̵����
	int groupCount = 0;

	while (m_running)
	{
		count = MarkData::MarkTextDataType[groupCount][0];
		m_count = MarkData::MarkTextDataType[groupCount][1];
		labels = MarkData::MarkTextDataType[groupCount][2];

		if (labels == 0)
		{
			// ������ݳ���
			int Rows = m_count - count + 1;

			// x����������
			xMarkData = new double[Rows]();

			// y����������
			yMarkData = new double[Rows]();

			// ��ȡ�������
			for (int i = 0; i < Rows; i++)
			{
				xMarkData[i] = MarkData::returnMarkData[count + i][0];
				yMarkData[i] = MarkData::returnMarkData[count + i][1];
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

			while (GetMarkStatus())
			{
				// �ȴ�20����
				QThread::msleep(30);

				// ��ȡ��λ��
				GetScannerPosition(xPos, yPos);

				// ������λ���ź�
				emit MarkRealPos(xPos, yPos);
			}
		}

		if (labels == 1)
		{
			// ������ݳ���
			int Rows = m_count - count;

			// x����������
			xMarkData = new double[Rows]();

			// y����������
			yMarkData = new double[Rows]();

			// �²�λ��
			zPos = MarkData::returnMarkData[m_count + 1][2];

			// ��ȡ�������
			for (int i = 0; i < Rows; i++)
			{
				xMarkData[i] = MarkData::returnMarkData[count + i][0];
				yMarkData[i] = MarkData::returnMarkData[count + i][1];
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

			while (GetMarkStatus())
			{
				// �ȴ�20����
				QThread::msleep(30);

				// ��ȡ��λ��
				GetScannerPosition(xPos, yPos);

				// ������λ���ź�
				emit MarkRealPos(xPos, yPos);
			}

			dPos[0] = zPos + GlobalInfo::presentSetZero;

			 // ����(�ƶ�z��λ��)
			returnValue = PI_MOV(ID, szAxes, dPos);
			if (!returnValue)
			{
				iError = PI_GetError(ID);
				PI_TranslateError(iError, szErrorMesage, 1024);
				emit EmitWrongInfo(szErrorMesage);
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

		// �ͷŶ�̬�ڴ�
		delete[]xMarkData;
		delete[]yMarkData;

		// �����һ��
		groupCount = groupCount + 1;

		if (groupCount == groupSize)
		{
			Stop();
			GlobalInfo::mthread = false;
			break;
		}		
	}
}

// �߳�ֹͣ
void markThread::Stop()
{
	// ֹͣ���ݷֽ�
	m_running = false;
}
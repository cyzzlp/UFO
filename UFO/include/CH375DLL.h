#ifndef _CH375_DLL_H
#define _CH375_DLL_H

#include <Windows.h>

#ifdef WIN32
#undef SHUT_FUNC_DECL
#ifdef SHUT_DLL_EXPORTS
#ifndef UNKNOWN_GCS_DLL
#define SHUT_FUNC_DECL __declspec(dllexport) WINAPI
#else
#define SHUT_FUNC_DECL WINAPI
#endif
#else
#define SHUT_FUNC_DECL __declspec(dllimport) WINAPI
#endif
#else
#define SHUT_FUNC_DECL
#endif

#ifndef WIN32
#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
#endif //WIN32

#define SHUT_FUNC_BOOL BOOL SHUT_FUNC_DECL
#define SHUT_FUNC_HANDLE HANDLE SHUT_FUNC_DECL
#define SHUT_FUNC_VOID VOID SHUT_FUNC_DECL

#ifdef __cplusplus
extern "C" {
#endif

#define  INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
	
#define		mOFFSET( s, m )			( (ULONG) & ( ( ( s * ) 0 ) -> m ) )	// �����ȡ�ṹ��Ա���ƫ�Ƶ�ַ�ĺ�

#ifndef		max
#define		max( a, b )				( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )	// �ϴ�ֵ
#endif

#ifndef		min
#define		min( a, b )				( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )	// ��Сֵ
#endif

#ifdef		ExAllocatePool
#undef		ExAllocatePool						// ɾ����TAG���ڴ����
#endif

#ifndef		NTSTATUS
typedef		LONG	NTSTATUS;					// ����״̬
typedef		long	LONG_PTR;					
#endif


typedef	struct	_USB_SETUP_PKT {				// USB���ƴ���Ľ����׶ε�����������ṹ
	UCHAR			mUspReqType;				// 00H ��������
	UCHAR			mUspRequest;				// 01H �������
	union	{
		struct	{
			UCHAR	mUspValueLow;				// 02H ֵ�������ֽ�
			UCHAR	mUspValueHigh;				// 03H ֵ�������ֽ�
		};
		USHORT		mUspValue;					// 02H-03H ֵ����
	};
	union	{
		struct	{
			UCHAR	mUspIndexLow;				// 04H �����������ֽ�
			UCHAR	mUspIndexHigh;				// 05H �����������ֽ�
		};
		USHORT		mUspIndex;					// 04H-05H ��������
	};
	USHORT			mLength;					// 06H-07H ���ݽ׶ε����ݳ���
} mUSB_SETUP_PKT, *mPUSB_SETUP_PKT;


#define		mCH375_PACKET_LENGTH	64			// CH375֧�ֵ����ݰ��ĳ���
#define		mCH375_PKT_LEN_SHORT	8			// CH375֧�ֵĶ����ݰ��ĳ���

typedef void* HANDLE;

typedef	struct	_WIN32_COMMAND {				// ����WIN32����ӿڽṹ
	union	{
		ULONG		mFunction;					// ����ʱָ�����ܴ�����߹ܵ���
		NTSTATUS	mStatus;					// ���ʱ���ز���״̬
	};
	ULONG			mLength;					// ��ȡ����,���غ������ݵĳ���
	union	{
		mUSB_SETUP_PKT	mSetupPkt;				// USB���ƴ���Ľ����׶ε���������
		UCHAR			mBuffer[ mCH375_PACKET_LENGTH ];	// ���ݻ�����,����Ϊ0��255B
	};
} mWIN32_COMMAND, *mPWIN32_COMMAND;


// WIN32Ӧ�ò�ӿ�����
#define		IOCTL_CH375_COMMAND		( FILE_DEVICE_UNKNOWN << 16 | FILE_ANY_ACCESS << 14 | 0x0f37 << 2 | METHOD_BUFFERED )	// ר�ýӿ�

#define		mWIN32_COMMAND_HEAD		mOFFSET( mWIN32_COMMAND, mBuffer )	// WIN32����ӿڵ�ͷ����

#define		mCH375_MAX_NUMBER		16			// ���ͬʱ���ӵ�CH375��

#define		mMAX_BUFFER_LENGTH		0x1000		// ���ݻ�������󳤶�4096

#define		mMAX_COMMAND_LENGTH		( mWIN32_COMMAND_HEAD + mMAX_BUFFER_LENGTH )	// ������ݳ��ȼ�������ṹͷ�ĳ���

#define		mDEFAULT_BUFFER_LEN		0x0400		// ���ݻ�����Ĭ�ϳ���1024

#define		mDEFAULT_COMMAND_LEN	( mWIN32_COMMAND_HEAD + mDEFAULT_BUFFER_LEN )	// Ĭ�����ݳ��ȼ�������ṹͷ�ĳ���


// CH375�˵��ַ
#define		mCH375_ENDP_INTER_UP	0x81		// CH375���ж������ϴ��˵�ĵ�ַ
#define		mCH375_ENDP_AUX_DOWN	0x01		// CH375�ĸ��������´��˵�ĵ�ַ
#define		mCH375_ENDP_DATA_UP		0x82		// CH375�����ݿ��ϴ��˵�ĵ�ַ
#define		mCH375_ENDP_DATA_DOWN	0x02		// CH375�����ݿ��´��˵�ĵ�ַ


// �豸��ӿ��ṩ�Ĺܵ���������
#define		mPipeDeviceCtrl			0x00000004	// CH375���ۺϿ��ƹܵ�
#define		mPipeInterUp			0x00000005	// CH375���ж������ϴ��ܵ�
#define		mPipeDataUp				0x00000006	// CH375�����ݿ��ϴ��ܵ�
#define		mPipeDataDown			0x00000007	// CH375�����ݿ��´��ܵ�
#define		mPipeAuxDown			0x00000008	// CH375�ĸ��������´��ܵ�

// Ӧ�ò�ӿڵĹ��ܴ���
#define		mFuncNoOperation		0x00000000	// �޲���
#define		mFuncGetVersion			0x00000001	// ��ȡ��������汾��
#define		mFuncGetConfig			0x00000002	// ��ȡUSB�豸����������
#define		mFuncSetExclusive		0x0000000b	// ���ö�ռʹ��
#define		mFuncResetDevice		0x0000000c	// ��λUSB�豸
#define		mFuncResetPipe			0x0000000d	// ��λUSB�ܵ�
#define		mFuncAbortPipe			0x0000000e	// ȡ��USB�ܵ�����������
#define		mFuncSetTimeout			0x0000000f	// ����USBͨѶ��ʱ
#define		mFuncBufferMode			0x00000010	// �趨�����ϴ�ģʽ����ѯ�������е����ݳ���
#define		mFuncBufferModeDn		0x00000011	// �趨�����´�ģʽ����ѯ�������е����ݳ���


// USB�豸��׼�������
#define		mUSB_CLR_FEATURE		0x01
#define		mUSB_SET_FEATURE		0x03
#define		mUSB_GET_STATUS			0x00
#define		mUSB_SET_ADDRESS		0x05
#define		mUSB_GET_DESCR			0x06
#define		mUSB_SET_DESCR			0x07
#define		mUSB_GET_CONFIG			0x08
#define		mUSB_SET_CONFIG			0x09
#define		mUSB_GET_INTERF			0x0a
#define		mUSB_SET_INTERF			0x0b
#define		mUSB_SYNC_FRAME			0x0c

// CH375���ƴ���ĳ���ר����������
#define		mCH375_VENDOR_READ		0xc0		// ͨ�����ƴ���ʵ�ֵ�CH375����ר�ö�����
#define		mCH375_VENDOR_WRITE		0x40		// ͨ�����ƴ���ʵ�ֵ�CH375����ר��д����

// CH375���ƴ���ĳ���ר���������
#define		mCH375_SET_CONTROL		0x51		// ��������ź�
#define		mCH375_GET_STATUS		0x52		// ����״̬�ź�

// �Ĵ�����λ����
#define		mBitInputRxd			0x02		// ֻ��,RXD#��������״̬,1:�ߵ�ƽ,0:�͵�ƽ
#define		mBitInputReq			0x04		// ֻ��,REQ#��������״̬,1:�ߵ�ƽ,0:�͵�ƽ


// ֱ�������״̬�źŵ�λ����
#define		mStateRXD				0x00000200	// RXD#��������״̬,1:�ߵ�ƽ,0:�͵�ƽ
#define		mStateREQ				0x00000400	// REQ#��������״̬,1:�ߵ�ƽ,0:�͵�ƽ

#define		MAX_DEVICE_PATH_SIZE	128			// �豸���Ƶ�����ַ���
#define		MAX_DEVICE_ID_SIZE		64			// �豸ID������ַ���


typedef		VOID	( CALLBACK	* mPCH375_INT_ROUTINE ) (  // �жϷ���ص�����
	PUCHAR			iBuffer );  // ָ��һ��������,�ṩ��ǰ���ж���������


SHUT_FUNC_HANDLE	CH375OpenDevice(  // ��CH375�豸,���ؾ��,��������Ч
	ULONG			iIndex );  // ָ��CH375�豸���,0��Ӧ��һ���豸,-1���Զ�����һ�����Ա��򿪵��豸���������


SHUT_FUNC_VOID	CH375CloseDevice(  // �ر�CH375�豸
	ULONG			iIndex );  // ָ��CH375�豸���


ULONG	WINAPI	CH375GetVersion( );  // ���DLL�汾��,���ذ汾��


ULONG	WINAPI	CH375DriverCommand(  // ֱ�Ӵ����������������,�����򷵻�0,���򷵻����ݳ���
	ULONG			iIndex,  // ָ��CH375�豸���,V1.6����DLLҲ�������豸�򿪺�ľ��
	mPWIN32_COMMAND	ioCommand );  // ����ṹ��ָ��
// �ó����ڵ��ú󷵻����ݳ���,������Ȼ��������ṹ,����Ƕ�����,�����ݷ���������ṹ��,
// ���ص����ݳ����ڲ���ʧ��ʱΪ0,�����ɹ�ʱΪ��������ṹ�ĳ���,�����һ���ֽ�,�򷵻�mWIN32_COMMAND_HEAD+1,
// ����ṹ�ڵ���ǰ,�ֱ��ṩ:�ܵ��Ż�������ܴ���,��ȡ���ݵĳ���(��ѡ),����(��ѡ)
// ����ṹ�ڵ��ú�,�ֱ𷵻�:����״̬����,�������ݵĳ���(��ѡ),
//   ����״̬��������WINDOWS����Ĵ���,���Բο�NTSTATUS.H,
//   �������ݵĳ�����ָ���������ص����ݳ���,���ݴ�������Ļ�������,����д����һ��Ϊ0


ULONG	WINAPI	CH375GetDrvVersion( );  // �����������汾��,���ذ汾��,�����򷵻�0


SHUT_FUNC_BOOL	CH375ResetDevice(  // ��λUSB�豸
	ULONG			iIndex );  // ָ��CH375�豸���


SHUT_FUNC_BOOL	CH375GetDeviceDescr(  // ��ȡ�豸������
	ULONG			iIndex,  // ָ��CH375�豸���
	PVOID			oBuffer,  // ָ��һ���㹻��Ļ�����,���ڱ���������
	PULONG			ioLength );  // ָ�򳤶ȵ�Ԫ,����ʱΪ׼����ȡ�ĳ���,���غ�Ϊʵ�ʶ�ȡ�ĳ���


SHUT_FUNC_BOOL	CH375GetConfigDescr(  // ��ȡ����������
	ULONG			iIndex,  // ָ��CH375�豸���
	PVOID			oBuffer,  // ָ��һ���㹻��Ļ�����,���ڱ���������
	PULONG			ioLength );  // ָ�򳤶ȵ�Ԫ,����ʱΪ׼����ȡ�ĳ���,���غ�Ϊʵ�ʶ�ȡ�ĳ���


SHUT_FUNC_BOOL	CH375SetIntRoutine(  // �趨�жϷ������
	ULONG			iIndex,  // ָ��CH375�豸���
	mPCH375_INT_ROUTINE	iIntRoutine );  // ָ���жϷ���ص�����,ΪNULL��ȡ���жϷ���,�������ж�ʱ���øó���


SHUT_FUNC_BOOL	CH375ReadInter(  // ��ȡ�ж�����
	ULONG			iIndex,  // ָ��CH375�豸���
	PVOID			oBuffer,  // ָ��һ���㹻��Ļ�����,���ڱ����ȡ���ж�����
	PULONG			ioLength );  // ָ�򳤶ȵ�Ԫ,����ʱΪ׼����ȡ�ĳ���,���غ�Ϊʵ�ʶ�ȡ�ĳ���


SHUT_FUNC_BOOL	CH375AbortInter(  // �����ж����ݶ�����
	ULONG			iIndex );  // ָ��CH375�豸���


SHUT_FUNC_BOOL	CH375ReadData(  // ��ȡ���ݿ�
	ULONG			iIndex,  // ָ��CH375�豸���
	PVOID			oBuffer,  // ָ��һ���㹻��Ļ�����,���ڱ����ȡ������
	PULONG			ioLength );  // ָ�򳤶ȵ�Ԫ,����ʱΪ׼����ȡ�ĳ���,���غ�Ϊʵ�ʶ�ȡ�ĳ���


SHUT_FUNC_BOOL	CH375AbortRead(  // �������ݿ������
	ULONG			iIndex );  // ָ��CH375�豸���


SHUT_FUNC_BOOL	CH375WriteData(  // д�����ݿ�
	ULONG			iIndex,  // ָ��CH375�豸���
	PVOID			iBuffer,  // ָ��һ��������,����׼��д��������
	PULONG			ioLength );  // ָ�򳤶ȵ�Ԫ,����ʱΪ׼��д���ĳ���,���غ�Ϊʵ��д���ĳ���


SHUT_FUNC_BOOL	CH375AbortWrite(  // �������ݿ�д����
	ULONG			iIndex );  // ָ��CH375�豸���


SHUT_FUNC_BOOL	CH375WriteRead(  // ��д����׼�����ݿ�(����),�ٶ�ȡ��׼�����ݿ�(Ӧ��)
	ULONG			iIndex,  // ָ��CH375�豸���
	PVOID			iBuffer,  // ָ��һ��������,����׼��д��������,���Ȳ�����mCH375_PACKET_LENGTH
	PVOID			oBuffer,  // ָ��һ���㹻��Ļ�����,���Ȳ�С��mCH375_PACKET_LENGTH,���ڱ����ȡ������
	PULONG			ioLength );  // ָ�򳤶ȵ�Ԫ,������mCH375_PACKET_LENGTH,����ʱΪ׼��д���ĳ���,���غ�Ϊʵ�ʶ�ȡ�ĳ���


SHUT_FUNC_BOOL	CH375GetStatus(  // ͨ��CH375ֱ���������ݺ�״̬
	ULONG			iIndex,  // ָ��CH375�豸���
	PULONG			iStatus );  // ָ��һ��˫�ֵ�Ԫ,���ڱ���״̬����
// λ7-λ0��ӦCH375��D7-D0����,λ9��ӦCH375��RXD#����,λ10��ӦCH375��REQ#����


SHUT_FUNC_BOOL	CH375SetTimeout(  // ����USB���ݶ�д�ĳ�ʱ
	ULONG			iIndex,  // ָ��CH375�豸���
	ULONG			iWriteTimeout,  // ָ��USBд�����ݿ�ĳ�ʱʱ��,�Ժ���mSΪ��λ,0xFFFFFFFFָ������ʱ(Ĭ��ֵ)
	ULONG			iReadTimeout );  // ָ��USB��ȡ���ݿ�ĳ�ʱʱ��,�Ժ���mSΪ��λ,0xFFFFFFFFָ������ʱ(Ĭ��ֵ)


SHUT_FUNC_BOOL	CH375WriteAuxData(  // д����������
	ULONG			iIndex,  // ָ��CH375�豸���
	PVOID			iBuffer,  // ָ��һ��������,����׼��д��������
	PULONG			ioLength );  // ָ�򳤶ȵ�Ԫ,����ʱΪ׼��д���ĳ���,���غ�Ϊʵ��д���ĳ���


SHUT_FUNC_BOOL	CH375SetExclusive(  // ���ö�ռʹ�õ�ǰCH375�豸
	ULONG			iIndex,  // ָ��CH375�豸���
	ULONG			iExclusive );  // Ϊ0���豸���Թ���ʹ��,��0���ռʹ��


ULONG	WINAPI	CH375GetUsbID(  // ��ȡUSB�豸ID,����������,��16λΪ����ID,��16λΪ��ƷID,����ʱ����ȫ0(��ЧID)
	ULONG			iIndex );  // ָ��CH375�豸���


PVOID	WINAPI	CH375GetDeviceName(  // ����ָ��CH375�豸���ƵĻ�����,�����򷵻�NULL
	ULONG			iIndex );  // ָ��CH375�豸���,0��Ӧ��һ���豸


SHUT_FUNC_BOOL	CH375SetBufUpload(  // �趨�ڲ������ϴ�ģʽ
	ULONG			iIndex,  // ָ��CH375�豸���,0��Ӧ��һ���豸
	ULONG			iEnableOrClear );  // Ϊ0���ֹ�ڲ������ϴ�ģʽ,ʹ��ֱ���ϴ�,��0�������ڲ������ϴ�ģʽ������������е���������
// ��������ڲ������ϴ�ģʽ,��ôCH375�������򴴽��߳��Զ�����USB�ϴ����ݵ��ڲ�������,ͬʱ����������е���������,��Ӧ�ó������CH375ReadData���������ػ������е���������


LONG	WINAPI	CH375QueryBufUpload(  // ��ѯ�ڲ��ϴ��������е��������ݰ�����,�ɹ��������ݰ�����,��������-1
	ULONG			iIndex );  // ָ��CH375�豸���,0��Ӧ��һ���豸


SHUT_FUNC_BOOL	CH375SetBufDownload(  // �趨�ڲ������´�ģʽ
	ULONG			iIndex,  // ָ��CH375�豸���,0��Ӧ��һ���豸
	ULONG			iEnableOrClear );  // Ϊ0���ֹ�ڲ������´�ģʽ,ʹ��ֱ���´�,��0�������ڲ������´�ģʽ������������е���������
// ��������ڲ������´�ģʽ,��ô��Ӧ�ó������CH375WriteData�󽫽����ǽ�USB�´����ݷŵ��ڲ�����������������,����CH375�������򴴽����߳��Զ�����ֱ�����


LONG	WINAPI	CH375QueryBufDownload(  // ��ѯ�ڲ��´��������е�ʣ�����ݰ�����(��δ����),�ɹ��������ݰ�����,��������-1
	ULONG			iIndex );  // ָ��CH375�豸���,0��Ӧ��һ���豸


SHUT_FUNC_BOOL	CH375ResetInter(  // ��λ�ж����ݶ�����
	ULONG			iIndex );  // ָ��CH375�豸���


SHUT_FUNC_BOOL	CH375ResetAux(  // ��λ��������д����
	ULONG			iIndex );  // ָ��CH375�豸���


SHUT_FUNC_BOOL	CH375ResetRead(  // ��λ���ݿ������
	ULONG			iIndex );  // ָ��CH375�豸���


SHUT_FUNC_BOOL	CH375ResetWrite(  // ��λ���ݿ�д����
	ULONG			iIndex );  // ָ��CH375�豸���


typedef		VOID	( CALLBACK	* mPCH375_NOTIFY_ROUTINE ) (  // �豸�¼�֪ͨ�ص�����
	ULONG			iEventStatus );  // �豸�¼��͵�ǰ״̬(�����ж���): 0=�豸�γ��¼�, 3=�豸�����¼�

#define		CH375_DEVICE_ARRIVAL		3		// �豸�����¼�,�Ѿ�����
#define		CH375_DEVICE_REMOVE_PEND	1		// �豸��Ҫ�γ�
#define		CH375_DEVICE_REMOVE			0		// �豸�γ��¼�,�Ѿ��γ�


SHUT_FUNC_BOOL	CH375SetDeviceNotify(  // �趨�豸�¼�֪ͨ����
	ULONG					iIndex,  // ָ��CH375�豸���,0��Ӧ��һ���豸
	PCHAR					iDeviceID,  // ��ѡ����,ָ���ַ���,ָ������ص��豸��ID,�ַ�����\0��ֹ
	mPCH375_NOTIFY_ROUTINE	iNotifyRoutine );  // ָ���豸�¼��ص�����,ΪNULL��ȡ���¼�֪ͨ,�����ڼ�⵽�¼�ʱ���øó���


SHUT_FUNC_BOOL	CH375SetTimeoutEx(  // ����USB���ݶ�д�ĳ�ʱ
	ULONG			iIndex,  // ָ��CH375�豸���
	ULONG			iWriteTimeout,  // ָ��USBд�����ݿ�ĳ�ʱʱ��,�Ժ���mSΪ��λ,0xFFFFFFFFָ������ʱ(Ĭ��ֵ)
	ULONG			iReadTimeout,  // ָ��USB��ȡ���ݿ�ĳ�ʱʱ��,�Ժ���mSΪ��λ,0xFFFFFFFFָ������ʱ(Ĭ��ֵ)
	ULONG			iAuxTimeout,  // ָ��USB�����´����ݵĳ�ʱʱ��,�Ժ���mSΪ��λ,0xFFFFFFFFָ������ʱ(Ĭ��ֵ)
	ULONG			iInterTimeout );  // ָ��USB�ж��ϴ����ݵĳ�ʱʱ��,�Ժ���mSΪ��λ,0xFFFFFFFFָ������ʱ(Ĭ��ֵ)


#ifdef __cplusplus
}
#endif

#endif		// _CH375_DLL_H
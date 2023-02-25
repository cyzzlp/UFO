#include "GlobalInfo.h"

// 静态变量初始化
QString GlobalInfo::aFileName = "No file be chose";
bool GlobalInfo::m_Connect = false;
bool GlobalInfo::p_Connect = false;
bool GlobalInfo::s_Connect = false;
bool GlobalInfo::c_Connect = false;
int GlobalInfo::ID = -1;
char GlobalInfo::szAxes[2] = { 'c' };
int GlobalInfo::MarkTextRows = 0;
int GlobalInfo::MarkTextColumns = 0;
unsigned long GlobalInfo::index{};
bool GlobalInfo::DataType = false;
bool GlobalInfo::mthread = false;
bool GlobalInfo::cthread = false;
bool GlobalInfo::pthread = false;
int GlobalInfo::MarkCount = 1;
double GlobalInfo::presentSetZero = 0.0;

GlobalInfo::GlobalInfo(QObject *parent)
	: QObject(parent)
{

}

GlobalInfo::~GlobalInfo()
{

}

#pragma once

#include <QObject>

class piRealpos  : public QObject
{
	Q_OBJECT

public:
	piRealpos(QObject *parent);
	~piRealpos();
};

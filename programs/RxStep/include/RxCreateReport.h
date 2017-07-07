#ifndef RXCREATEREPORT_H_
#define RXCREATEREPORT_H_

#include "RxBlock.h"
#include "RxSampling.h"

class RxCreateReport : public RxBlock
{
	Q_OBJECT
public:
	RxCreateReport (RxBlock* prev, const QString& reportFileName, const QString& tempDir);
private:
	void run();
private:
	QString m_reportFileName;
	QString m_tempDir;
};

#endif /*RXCREATEREPORT_H_*/

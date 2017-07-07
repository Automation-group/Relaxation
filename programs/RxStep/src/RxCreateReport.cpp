#include "RxCreateReport.h"
#include <QProcess>
#include <QDir>
#include <QStringList>
#include <algorithm>
#include <functional>

#include <QtDebug>

RxCreateReport::RxCreateReport (RxBlock* prev, const QString& reportFileName, const QString& tempDir)
	: RxBlock(prev), m_reportFileName(reportFileName), m_tempDir(tempDir)
{
	
}
void RxCreateReport::run()
{
	QStringList fileList = QDir(m_tempDir).entryList(QDir::Files);
	
	fileList.push_front(m_reportFileName);
	
	QProcess process;
	process.setWorkingDirectory(m_tempDir);
	process.start ("zip", fileList);
	process.waitForFinished();
	doNext();
}

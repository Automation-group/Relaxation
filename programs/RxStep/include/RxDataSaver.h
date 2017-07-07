#ifndef RXDATASAVER_H_
#define RXDATASAVER_H_

#include <QObject>
#include <QPolygon>
#include <QFile>
#include <QTextStream>
#include <QRlxData.h>

class RxDataSaver : public QObject
{
	Q_OBJECT
public:
	RxDataSaver(const QString& tempPath, const QRlxPattern& pattern);
public Q_SLOTS:
	void measurementReady (const QPolygonF& data, double force, double rlx);
	void endLoading(double deformation);
private:
	int m_dataCounter;
	QString m_tempPath;
	double m_deformation;
	QRlxPattern m_pattern;
};

#endif /*RXDATASAVER_H_*/

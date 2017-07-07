#include "RxDataSaver.h"
#include <QFile>
#include <QTextStream>

RxDataSaver::RxDataSaver(const QString& tempPath, const QRlxPattern& pattern)
	: m_dataCounter(0), m_tempPath(tempPath),
	m_deformation(0.0), m_pattern(pattern)
{

}

void RxDataSaver::endLoading(double deformation)
{
	m_deformation += deformation;
}

void RxDataSaver::measurementReady (const QPolygonF& data, double force, double rlx)
{
	QString fileName = m_tempPath + QString::fromUtf8("Step") +
		QString::number(++m_dataCounter) + QString::fromUtf8(".csv");

	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly)) return;

	QTextStream textStream(&file);

	QPointF i;
	Q_FOREACH(i, data)
		textStream << QString::number(i.x()).replace(".", ",") << ";"
		<< QString::number(i.y()).replace(".", ",") << "\n";

	file.close();

	static bool firstRun = true;
	QFile generalDataFile(m_tempPath + QString::fromUtf8("Data.csv"));
	if(generalDataFile.open(QIODevice::Append) || generalDataFile.open(QIODevice::WriteOnly))
	{
		QTextStream generalDataStream(&generalDataFile);
		if (firstRun)
		{
			firstRun = false;
			generalDataStream << QString::fromUtf8("Δσ,% ;F,Н ;σ,МПа ;ε,мм \n");
		}

		generalDataStream << QString::number(rlx).replace(".", ",") << ";"
			<< QString::number(force).replace(".", ",") << ";"
			<< QString::number(force / (m_pattern.getArea() * 1e6)).replace(".", ",") << ";"
			<< QString::number(m_deformation).replace(".", ",") << "\n";
		generalDataFile.close();
	}
}

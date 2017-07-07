#include "RxXmlSettings.h"
#include <QtAlgorithms>
#include <QXmlStreamWriter>

bool rxReadXmlFile(QIODevice &device, QSettings::SettingsMap &map)
{
	return false;
}

bool rxWriteXmlFile(QIODevice &device, const QSettings::SettingsMap &map)
{
	QXmlStreamWriter writer(&device);
	writer.setAutoFormatting(true);
	writer.writeStartDocument("1.0");
	writer.writeDTD("<!DOCTYPE properties SYSTEM \"http://java.sun.com/dtd/properties.dtd\">");
	writer.writeStartElement("properties");

	QSettings::SettingsMap::const_iterator iter = map.begin();
	QSettings::SettingsMap::const_iterator end = map.end();
	while(end != iter)
	{
		writer.writeStartElement("entry");
		writer.writeAttribute("key", iter.key());
		writer.writeCharacters(iter.value().toString());
		writer.writeEndElement();		
		iter++;
	}
		
	writer.writeEndElement();
	writer.writeEndDocument();
	return true;
}

QSettings::Format XmlFormat()
{
	static const QSettings::Format _XmlFormat =
        QSettings::registerFormat("xml", rxReadXmlFile, rxWriteXmlFile);	
	return _XmlFormat;
}

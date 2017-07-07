#include "QRlxData.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QTextCodec>
#include <QString>
#include <QtDebug>
#include <QStringList>
#include <QtAlgorithms>
#include <QXmlStreamWriter>
#include <QFile>

void QRlxPattern::save(const QString& filename) const
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly)) return;
	
	QXmlStreamWriter writer(&file);
	writer.setAutoFormatting(true);
	//writer.setCodec("UTF-8");
	writer.writeStartDocument("1.0");
	writer.writeDTD("<!DOCTYPE properties SYSTEM \"http://java.sun.com/dtd/properties.dtd\">");
	writer.writeStartElement("properties");
	
		writer.writeStartElement("entry");
		writer.writeAttribute("key", "D1");
		writer.writeCharacters(QString::number(d1));
		writer.writeEndElement();
	
		writer.writeStartElement("entry");
		writer.writeAttribute("key", "D2");
		writer.writeCharacters(QString::number(d2));
		writer.writeEndElement();

		writer.writeStartElement("entry");
		writer.writeAttribute("key", "Lenght");
		writer.writeCharacters(QString::number(height));
		writer.writeEndElement();

		writer.writeStartElement("entry");
		writer.writeAttribute("key", "Name");
		writer.writeCharacters(name);
		writer.writeEndElement();

		writer.writeStartElement("entry");
		writer.writeAttribute("key", "Description");
		writer.writeCharacters(description);
		writer.writeEndElement();

		writer.writeStartElement("entry");
		writer.writeAttribute("key", "Form");
		writer.writeCharacters(QString::fromUtf8(form == Round ? "Round" : "Rectangle"));
		writer.writeEndElement();
		
	writer.writeEndElement();
	writer.writeEndDocument();
	/*
	QSettings settings(filename, QSettings::IniFormat);
	settings.setValue("D1", d1);
	settings.setValue("D2", d2);
	settings.setValue("Lenght", height);
	settings.setValue("Name", name);
	settings.setValue("Description", description);
	settings.setValue("Form", QString::fromUtf8(form == Round ? "Round" : "Rectangle"));
	
	QXmlStreamWriter
	*/	
}

void QRlxData::clear ()
{
  name = "";
  data.clear ();
  eventList.clear ();
  paramList.clear ();
}

QRlxEvent QRlxData::loadEvent (QXmlStreamReader& xmlreader)
{
  QStringRef timeRef = xmlreader.attributes ().value (tr("Время"));
  QString time = "-1";
  if (!timeRef.isNull ()) time = timeRef.toString ();

  QString name = xmlreader.qualifiedName ().toString ();
  while (!xmlreader.isEndElement ()) xmlreader.readNext();
  return QRlxEvent (name, time.toDouble ());
}

void QRlxData::loadEvents (QXmlStreamReader& xmlreader)
{
  if (xmlreader.qualifiedName () != tr("События")) return;
  xmlreader.readNext();
  while (!xmlreader.isEndElement ())
  {
    if (xmlreader.isStartElement ())
    {
      eventList.push_back ( loadEvent (xmlreader) );
    }
    xmlreader.readNext();
  }  
}

QRlxPattern QRlxData::loadPattern (QXmlStreamReader& xmlreader)
{
  QString name;
  QString description;
  QString d1, d2, height, strform;
  
  QStringRef buf = xmlreader.attributes ().value (tr("Высота"));
  if (!buf.isNull ()) height = buf.toString ();
  
  buf = xmlreader.attributes ().value (tr("D1"));
  if (!buf.isNull ()) d1 = buf.toString ();

  buf = xmlreader.attributes ().value (tr("D2"));
  if (!buf.isNull ()) d2 = buf.toString ();

  buf = xmlreader.attributes ().value (tr("Форма"));
  if (!buf.isNull ()) strform = buf.toString ();

  bool isName = false;
  bool isDescription = false;
  
  int level = 1;
  xmlreader.readNext();
  while (level)
  {
    if (xmlreader.isStartElement ()) level++;
    if (level == 2)
    {
      if (xmlreader.qualifiedName () == tr("Имя")) isName = true;
      if (xmlreader.qualifiedName () == tr("Описание")) isDescription = true;
      
      if (isName && xmlreader.isCharacters ())
      {
        isName = false;
        name = xmlreader.text ().toString ();
      }
      
      if (isDescription && xmlreader.isCharacters ())
      {
        isDescription = false;
        description = xmlreader.text ().toString ();
      }      
    }
    xmlreader.readNext();
    if (xmlreader.isEndElement ()) level --;
    if (level == 1)
    {
      isName = false;
      isDescription = false;
    }
  }
  QRlxPattern::Form form = QRlxPattern::Rectangle; 
  if (strform == tr("Круглый")) form = QRlxPattern::Round;
  
  return QRlxPattern (name, description, d1.toDouble (), d2.toDouble (), 
      height.toDouble (), form);
}

void QRlxData::loadParams (QXmlStreamReader& xmlreader)
{
  if (xmlreader.qualifiedName () != tr("Параметры_Эксперимента")) return;
  
  //QString strDateTime;
  
  QStringRef buf = xmlreader.attributes ().value (tr("Дата"));
  if (!buf.isNull ())
  {
    dateTime = QDateTime::fromString (buf.toString (), "dd.MM.yy hh:mm:ss");
    dateTime = dateTime.addYears (100);
  }
  
  xmlreader.readNext();
  while (!xmlreader.isEndElement ())
  {
    if (xmlreader.isStartElement ())
    {
      paramList.push_back ( loadParam (xmlreader) );
    }
    xmlreader.readNext();
  }   
}

QRlxParam QRlxData::loadParam (QXmlStreamReader& xmlreader)
{
  QString name = xmlreader.qualifiedName ().toString ();
  QString value;
  while (!xmlreader.isEndElement ())
  {
    if (xmlreader.isCharacters ())
      value = xmlreader.text ().toString ();
    xmlreader.readNext();
  }
  return QRlxParam (name, value.toDouble ());  
}

void QRlxData::loadDataSet (QXmlStreamReader& xmlreader)
{
  if (xmlreader.qualifiedName () != tr("Данные")) return;
  xmlreader.readNext();
  while (!xmlreader.isEndElement ())
  {
    if (xmlreader.isStartElement ())
    {
      if (xmlreader.qualifiedName ().toString (). startsWith (tr("Данные")))
        data.push_back ( loadData (xmlreader) );
    }
    xmlreader.readNext();
  }   
}

QPolygonF QRlxData::loadData (QXmlStreamReader& xmlreader)
{
  QStringList forceList;
  QStringList timeList;
  
  int level = 1;    
  while (level)
  {
    xmlreader.readNext();
    if (xmlreader.isEndElement ()) level--;
    if (!xmlreader.isStartElement ()) continue;
    level ++;
    if (level != 2) continue;
    
    int datacode = 0; // 1 сила, 2 время

    if (xmlreader.qualifiedName () == tr("Сила"))
      datacode = 1;
    
    if (xmlreader.qualifiedName () == tr("Время"))
      datacode = 2;
    
    while (!xmlreader.isCharacters () && level > 1)
    {
      xmlreader.readNext();
      if (xmlreader.isEndElement ()) level--;
      if (xmlreader.isStartElement ()) level++;
    }
    
    if (level != 2) continue;
    
    switch (datacode)
    {
    case 1: forceList = xmlreader.text ().toString ().split ("\n"); 
    case 2: timeList = xmlreader.text ().toString ().split ("\n");
    }
  }
  
  int size = qMin (forceList.size (), timeList.size ());
  QPolygonF data;
  data.reserve (size);
  for (int i = 0; i < (size - 1); i++)
  {
    double x = timeList[i].toDouble ();
    double y = forceList[i].toDouble ();
    data << QPointF (x, y);
  }
  
  return data;
}

void QRlxData::load (QIODevice* device)
{
  clear ();
  QXmlStreamReader xmlreader (device);
  /*
  xmlwriter.writeAttribute (tr("Эксперимент"), name);
  QStringRef buf = xmlreader.attributes ().value (tr("Высота"));
  if (!buf.isNull ()) height = buf.toString ();
 */ 
  int level = 0;
  while (!xmlreader.atEnd ())
  {
    bool isStartElement = xmlreader.isStartElement ();
    if (isStartElement) level++;
    
    if (isStartElement && level == 1)
    {
      QStringRef buf = xmlreader.attributes ().value (tr("Эксперимент"));
      if (!buf.isNull ()) name = buf.toString ();      
    }
    
    if (isStartElement && level == 2)
    {
      if (xmlreader.qualifiedName () == tr("События")) loadEvents (xmlreader);
      if (xmlreader.qualifiedName () == tr("Данные")) loadDataSet (xmlreader);
      if (xmlreader.qualifiedName () == tr("Параметры_Эксперимента")) loadParams (xmlreader);
      if (xmlreader.qualifiedName () == tr("Образец")) _pattern = loadPattern (xmlreader);
    }
    
    if (xmlreader.isEndElement ()) level--;
    xmlreader.readNext();
  }
}

void QRlxData::savePattern (QXmlStreamWriter& xmlwriter)
{
  xmlwriter.writeStartElement (tr("Образец"));
  xmlwriter.writeAttribute (tr("Высота"), QString::number(_pattern.getHeight (), 'f', 6));
  xmlwriter.writeAttribute (tr("D1"), QString::number(_pattern.getD1 (), 'f', 6));
  xmlwriter.writeAttribute (tr("D2"), QString::number(_pattern.getD2 (), 'f', 6));
  double area = _pattern.getD1 () * _pattern.getD2 ();
  switch (_pattern.getForm ())
  {
  case QRlxPattern::Round:
    xmlwriter.writeAttribute (tr("Форма"), tr("Круглый"));
    area *= 3.1415926535897931 / 4.0; 
    break;
  case QRlxPattern::Rectangle:
    xmlwriter.writeAttribute (tr("Форма"), tr("Квадратный"));
    break;
  }
  
  xmlwriter.writeAttribute (tr("Площадь"), QString::number(area));
  
  xmlwriter.writeStartElement (tr("Имя"));
  xmlwriter.writeCharacters (_pattern.getName ());
  xmlwriter.writeEndElement ();

  xmlwriter.writeStartElement (tr("Описание"));
  xmlwriter.writeCharacters (_pattern.getDescription ());
  xmlwriter.writeEndElement ();
  
  xmlwriter.writeEndElement ();
}

void QRlxData::saveParams (QXmlStreamWriter& xmlwriter)
{
  xmlwriter.writeStartElement (tr("Параметры_Эксперимента"));
  xmlwriter.writeAttribute (tr("Дата"), dateTime.toString ("dd.MM.yy hh:mm:ss"));
  
  for (ParamList::const_iterator i = paramList.constBegin (); i != paramList.constEnd (); ++i)
  {
    xmlwriter.writeStartElement ((*i).getName ());
    xmlwriter.writeCharacters (QString::number ((*i).getValue ()));
    xmlwriter.writeEndElement ();
  }
  xmlwriter.writeEndElement ();
}

void QRlxData::saveDataSet (QXmlStreamWriter& xmlwriter)
{
  xmlwriter.writeStartElement (tr("Данные"));
  xmlwriter.writeAttribute (tr("Шагов_Нагружения"), QString::number (data.size ()));
  
  int counter = 0;
  for (DataSet::const_iterator i = data.constBegin (); i != data.constEnd (); ++i)
  {
    xmlwriter.writeStartElement (tr("Данные") + QString::number (counter));
    
    const QPolygonF& temp = *i;
    
      xmlwriter.writeStartElement (tr("Сила"));
      for (QPolygonF::const_iterator j = temp.constBegin (); j != temp.constEnd (); ++j)
        xmlwriter.writeCharacters (QString::number ((*j).y(), 'f', 2) + "\n");
      xmlwriter.writeEndElement ();

      xmlwriter.writeStartElement (tr("Время"));
      for (QPolygonF::const_iterator j = temp.constBegin (); j != temp.constEnd (); ++j)
        //xmlwriter.writeCharacters (QString::number ((*j).x(), 'f', 2) + "\n");
    	  xmlwriter.writeCharacters (QString::number (static_cast<int>( (*j).x())) + "\n");
      xmlwriter.writeEndElement ();
      
    xmlwriter.writeEndElement ();
    counter ++;
  }
  
  xmlwriter.writeEndElement ();  
}

void QRlxData::saveEvents (QXmlStreamWriter& xmlwriter)
{
  xmlwriter.writeStartElement (tr("События"));
  
  for (EventList::const_iterator i = eventList.constBegin (); i != eventList.constEnd () ; ++i)
  {
    xmlwriter.writeEmptyElement ((*i).getName ());
    xmlwriter.writeAttribute (tr("Время"), QString::number ((*i).getTime (), 'f', 2));
    //xmlwriter.writeEndElement ();
  }
  
  xmlwriter.writeEndElement ();  
}

void QRlxData::save (QIODevice* device)
{
  QXmlStreamWriter xmlwriter(device);
  //xmlwriter.setCodec (QTextCodec::codecForName("UTF-8"));
  xmlwriter.writeStartDocument ("1.0");
  
  xmlwriter.writeStartElement (tr("Рояль"));
  xmlwriter.writeAttribute (tr("Эксперимент"), name);
  
  savePattern (xmlwriter);
  saveParams (xmlwriter);
  saveEvents (xmlwriter);
  saveDataSet (xmlwriter);
  
  xmlwriter.writeEndElement ();
  xmlwriter.writeEndDocument ();
}

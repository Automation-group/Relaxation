#ifndef QRLXDATA_H_
#define QRLXDATA_H_

#include <QIODevice>
#include <QPolygonF>
#include <QList>
#include <QDateTime>

class QXmlStreamWriter;
class QXmlStreamReader; 

class QRlxPattern
{
public:
  enum Form {Round, Rectangle};
  
  QRlxPattern () { }
  
  QRlxPattern (const QString& name, const QString& description,
      double d1, double d2, double height, Form form)
    : name (name), description (description),
    d1 (d1), d2 (d2), height (height), form (form)
    { }
  
  QString getName () const { return name; }
  void setName (const QString& name) { QRlxPattern::name = name; }
  
  QString getDescription () const { return description; }
  void setDescription (const QString& description) { QRlxPattern::description = description; }
  
  double getHeight () const { return height; }
  void setHeight (double height) { QRlxPattern::height = height; }
  
  double getD1 () const { return d1; }
  void setD1 (double d1) { QRlxPattern::d1 = d1; }
  
  double getD2 () const { return d2; }
  void setD2 (double d2) { QRlxPattern::d2 = d2; }
  
  double getArea () const
  {
    double area = d1 * d2;
    if (form == Round) area *= 3.1415926535897931 / 4.0;
    return area;
  }
  
  Form getForm () { return form; }
  void setForm (Form form) { QRlxPattern::form = form; }
  
  void save(const QString& filename) const;
private:
  double d1;
  double d2;
  double height;
  QString name;
  QString description;
  Form form;
};

class QRlxEvent
{
public:
  QRlxEvent (const QString& name, double time)
    : name (name), time (time) { }
  QString getName () const { return name; }
  double getTime () const { return time; }
private:
  QString name;
  double time;
};


class QRlxParam
{
public:
  QRlxParam (const QString& name, double value)
    : name (name), value (value) { }
  QString getName () const { return name; }
  double getValue () const { return value; }
private:
  QString name;
  double value;
};

class QRlxData: public QObject
{
  Q_OBJECT
public:
  typedef QList<QPolygonF> DataSet;
  typedef QList<QRlxEvent> EventList;
  typedef QList<QRlxParam> ParamList;
public:
  void load (QIODevice* device);
  void save (QIODevice* device);
  void clear ();
  EventList& events () { return eventList; }
  DataSet& dataSet () { return data; }
  QRlxPattern& pattern () { return _pattern; }
  const DataSet& dataSet () const { return data; }
  ParamList& params () { return paramList; }
  
  void setDateTime (const QDateTime& dateTime) { QRlxData::dateTime = dateTime; }
  QDateTime getDateTime () const { return dateTime; }
  
  void setName (const QString& name) { QRlxData::name = name; }
  QString getName () const { return name; }
private:
  void savePattern (QXmlStreamWriter& xmlwriter);
  QRlxPattern loadPattern (QXmlStreamReader& xmlreader);
  
  void saveParams (QXmlStreamWriter& xmlwriter);
  void loadParams (QXmlStreamReader& xmlreader);
  QRlxParam loadParam (QXmlStreamReader& xmlreader);
  
  void saveDataSet (QXmlStreamWriter& xmlwriter);
  void saveEvents (QXmlStreamWriter& xmlwriter);
  
  void loadEvents (QXmlStreamReader& xmlreader);
  QRlxEvent loadEvent (QXmlStreamReader& xmlreader);
  
  void loadDataSet (QXmlStreamReader& xmlreader);
  QPolygonF loadData (QXmlStreamReader& xmlreader);
private:
  QRlxPattern _pattern;
  DataSet data;
  EventList eventList;
  ParamList paramList;
  QDateTime dateTime;
  QString name;
};

#endif /*QRLXDATA_H_*/

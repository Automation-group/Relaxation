#ifndef SEARCHDEVICES_H_
#define SEARCHDEVICES_H_

#include <QString>
#include <QlfTUB.h>
#include <QlfSMD.h>

class SearchDevices
{
  public:
    void SearchDev(QString *portSMD, QString *portTUB);
  private:
    QlfTUB* tub;
    QlfSMD* smd;
  protected:
    bool SearchSMD(QString port);
    bool SearchTUB(QString port);
};

#endif /*SEARCHDEVICES_H_*/

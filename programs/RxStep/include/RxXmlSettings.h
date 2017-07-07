#ifndef RXXMLSETTINGS_H_
#define RXXMLSETTINGS_H_

#include <QSettings>

bool rxReadXmlFile(QIODevice &device, QSettings::SettingsMap &map);
bool rxWriteXmlFile(QIODevice &device, const QSettings::SettingsMap &map);
QSettings::Format XmlFormat();

#endif /*RXXMLSETTINGS_H_*/

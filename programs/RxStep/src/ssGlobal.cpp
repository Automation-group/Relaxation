#include "ssGlobal.h"


QSettings& ssSettings ()
{
  static QSettings settings (QSettings::IniFormat, QSettings::UserScope, "Lab5", "RxStep");
  return settings;
}

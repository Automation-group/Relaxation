#ifndef EXPERIMENTWIZARD_H_
#define EXPERIMENTWIZARD_H_

#include <QWizard>
#include <QSettings>
#include <QRlxData.h>
#include <boost/shared_ptr.hpp>

#include "RxSelectReportFile.h"

class Ui_PatternWizardForm;	
class Ui_ExpSettingsForm;
class Ui_SetPatternForm;

class ExperimentWizard : public QWizard
{
	Q_OBJECT
public:
	ExperimentWizard();
	void getSettings(QSettings& settings);
	QRlxPattern getPattern() const;
	
	double getLoadingSpeed() const;
	double getLoadingDeformation() const;
	double getRelaxTime() const;
	int getStepCount() const;
	QString reportFileName() const;
	
Q_SIGNALS:
	/**
	* Запустить двигатель (нагружение) 
	*/
	void runMoveUp ();

	/**
	 * Запустить двигатель (разгружение)
	 */
	void runMoveDown ();

	/**
	 * Остановить двигатель
	 */
	void stopMove ();

private Q_SLOTS:
	void saveDialog();
	void loadDialog();
private:
	boost::shared_ptr<Ui_PatternWizardForm> m_patterWForm;	
	boost::shared_ptr<Ui_ExpSettingsForm> m_settingsWForm;
	boost::shared_ptr<Ui_SetPatternForm> m_setPatternForm;
	RxSelectReportFile* m_srfForm;
};

#endif /*EXPERIMENTWIZARD_H_*/

#include "ExperimentWizard.h"
#include <QWizardPage>
#include <QFileInfo>
#include <QDir>

#include "ui_PatternWizardPage.h"
#include "ui_ExpSettingsWizardPage.h"
#include "ui_SetPatternWizardPage.h"

#include "ssGlobal.h"

ExperimentWizard::ExperimentWizard()
	: m_patterWForm(new Ui_PatternWizardForm),
	m_settingsWForm(new Ui_ExpSettingsForm),
	m_setPatternForm(new Ui_SetPatternForm),
	m_srfForm(new RxSelectReportFile)
{
	QWizardPage* page = new QWizardPage();
	m_patterWForm->setupUi(page);
	addPage(page);

	page = new QWizardPage();
	m_settingsWForm->setupUi(page);
	addPage(page);

	page = new QWizardPage();
	m_setPatternForm->setupUi(page);
	addPage(page);

	addPage(m_srfForm);

	connect(m_setPatternForm->pbMoveUp, SIGNAL(clicked()), this, SIGNAL(runMoveUp()) );
	connect(m_setPatternForm->pbMoveStop, SIGNAL(clicked()), this, SIGNAL(stopMove()) );
	connect(m_setPatternForm->pbMoveDown, SIGNAL(clicked()), this, SIGNAL(runMoveDown()) );

	loadDialog();

	connect (this, SIGNAL (finished (int)), this, SLOT(saveDialog ()) );

}

QRlxPattern ExperimentWizard::getPattern() const
{
	return QRlxPattern(m_patterWForm->lePatternName->text(),
			m_patterWForm->tePatternDescription->toPlainText(),
			m_patterWForm->dsbPatternWidth -> value() * 1e-3,
			m_patterWForm->dsbPatternThickness -> value() * 1e-3,
			m_patterWForm->dsbPatternLenght -> value() * 1e-3,
			m_patterWForm->rbPatternRoundSection -> isChecked() ? QRlxPattern::Round
					: QRlxPattern::Rectangle);
}

QString ExperimentWizard::reportFileName() const
{
	return m_srfForm->fileName();
}

double ExperimentWizard::getLoadingDeformation() const
{
	return getLoadingSpeed() * m_settingsWForm->dsbExpLoadingTime -> value();
}

double ExperimentWizard::getLoadingSpeed() const
{
	return m_patterWForm->dsbPatternLenght -> value() * m_settingsWForm->dsbExpLoadingSpeed -> value()
			/ 100.0;
}

double ExperimentWizard::getRelaxTime() const
{
	return m_settingsWForm->sbExpRelaxationTime->value();
}

int ExperimentWizard::getStepCount() const
{
	return m_settingsWForm->sbExpStepCount -> value();
}


void ExperimentWizard::getSettings(QSettings& settings)
{
	settings.setValue(QString::fromUtf8("Образец_Название"), m_patterWForm->lePatternName -> text());
	settings.setValue(QString::fromUtf8("Образец_Описание"), m_patterWForm->tePatternDescription -> toPlainText());
	settings.setValue(QString::fromUtf8("Образец_Толщина"), m_patterWForm->dsbPatternThickness -> value());
	settings.setValue(QString::fromUtf8("Образец_Ширина"), m_patterWForm->dsbPatternWidth -> value());
	settings.setValue(QString::fromUtf8("Образец_Длина"), m_patterWForm->dsbPatternLenght -> value());

	if (m_patterWForm->rbPatternRoundSection -> isChecked())
		settings.setValue(QString::fromUtf8("Образец_Сечение"), QString::fromUtf8("Круглое"));
	else
		settings.setValue(QString::fromUtf8("Образец_Сечение"), QString::fromUtf8("Квадратное"));

	settings.setValue(QString::fromUtf8("Образец_МодульУпругости"), m_settingsWForm->dsbCoefficientOfElasticity->value());

	settings.setValue(QString::fromUtf8("Тип_нагружения"),
			m_settingsWForm->rbStrainStep->isChecked() ? QString::fromUtf8("Деформация") : QString::fromUtf8("Напряжение"));

	settings.setValue(QString::fromUtf8("Шагов_нагружения"), m_settingsWForm->sbExpStepCount -> value());
	settings.setValue(QString::fromUtf8("Время_релаксации"), m_settingsWForm->sbExpRelaxationTime -> value());
	settings.setValue(QString::fromUtf8("Скорость_нагружения"),
			m_settingsWForm->dsbExpLoadingSpeed -> value());

	if (m_settingsWForm->rbStrainStep->isChecked())
		settings.setValue(QString::fromUtf8("Время_нагружения"), m_settingsWForm->dsbExpLoadingTime -> value());

	if (m_settingsWForm->rbStressStep->isChecked())
		settings.setValue(QString::fromUtf8("Шаг_нагружения"), m_settingsWForm->dsbStressStep -> value());

	settings.setValue(QString::fromUtf8("Файл_отчета"), m_srfForm->fileName());
}

void ExperimentWizard::saveDialog()
{
	getSettings(ssSettings());
}

void ExperimentWizard::loadDialog()
{

	double buf = 0.0;

	buf = ssSettings ().value( QString::fromUtf8("Образец_Толщина"), 0.0).toDouble();
	m_patterWForm->dsbPatternThickness -> setValue(buf);
	buf = ssSettings ().value( QString::fromUtf8("Образец_Ширина"), 0.0).toDouble();
	m_patterWForm->dsbPatternWidth -> setValue(buf);
	buf = ssSettings ().value( QString::fromUtf8("Образец_Длина"), 0.0).toDouble();
	m_patterWForm->dsbPatternLenght -> setValue(buf);

	bool roundChecked = ssSettings ().value(tr("Образец_Сечение"), tr("Круглое")).toString() == tr("Круглое");
	m_patterWForm->rbPatternRoundSection -> setChecked(roundChecked);
	m_patterWForm->rbPatternRectangleSection -> setChecked( !roundChecked);

	m_settingsWForm->dsbCoefficientOfElasticity->setValue(
			ssSettings().value(QString::fromUtf8("Образец_МодульУпругости")).toDouble()
					);

	buf = ssSettings ().value( QString::fromUtf8("Шагов_Нагружения"), 0).toInt();
	m_settingsWForm->sbExpStepCount -> setValue((int)buf);
	buf = ssSettings ().value( QString::fromUtf8("Скорость_Нагружения"), 0.0).toDouble();
	m_settingsWForm->dsbExpLoadingSpeed -> setValue(buf);
	buf = ssSettings ().value( QString::fromUtf8("Время_Нагружения"), 0.0).toDouble();
	m_settingsWForm->dsbExpLoadingTime -> setValue(buf);

	QString lastFile = ssSettings ().value( QString::fromUtf8("Файл_отчета")).toString();
	m_srfForm->setFileName(QFileInfo (lastFile).absolutePath() + QDir::separator() );
}



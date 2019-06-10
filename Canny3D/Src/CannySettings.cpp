#include "CannySettings.h"
#include "Settings.h"

CannySettings::CannySettings(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void CannySettings::setVOICenterMinimum(int value)
{
	ui.centerVal->setMinimum(value);
	ui.centerSlider->setMinimum(value);
}
void CannySettings::setVOICenterMaximum(int value)
{
	ui.centerVal->setMaximum(value);
	ui.centerSlider->setMaximum(value);
}

void CannySettings::setVOIWidthMinimum(int value)
{
	ui.widthVal->setMinimum(value);
	ui.widthSlider->setMinimum(value);
}

void CannySettings::setVOIWidthMaximum(int value)
{
	ui.widthVal->setMaximum(value);
	ui.widthSlider->setMaximum(value);
}

void CannySettings::emitSettingsChanged()
{
	emit settingsChanged(currentSettings());
}

Settings CannySettings::currentSettings() const
{
	auto s = Settings{};

	s.voiCenter = ui.centerVal->value();
	s.voiWidth = ui.widthVal->value();
	s.gaussKernel = ui.gaussKernel->value();
	s.gaussSigma = ui.gaussSigma->value();
	s.cannyLow = ui.cannyLow->value();
	s.cannyHigh = ui.cannyHigh->value();
	if (ui.radioVoi->isChecked()) s.step = Steps::VOI;
	if (ui.radioGauss->isChecked()) s.step = Steps::Gauss;
	if (ui.radioCanny->isChecked()) s.step = Steps::Canny;

	return s;
}

void CannySettings::setUiValues(Settings const& s) const
{
	ui.centerMin->setValue(-300); 
	ui.centerMax->setValue(2000);
	ui.centerVal->setValue(s.voiCenter);
	
	ui.widthMin->setValue(2); 
	ui.widthMax->setValue(6000);
	ui.widthVal->setValue(s.voiWidth);

	ui.gaussKernel->setValue(s.gaussKernel);
	ui.gaussSigma->setValue(s.gaussSigma);
	ui.cannyLow->setValue(s.cannyLow);
	ui.cannyHigh->setValue(s.cannyHigh);

	switch (s.step)
	{
	case Steps::VOI: ui.radioVoi->setChecked(true); break;
	case Steps::Gauss: ui.radioGauss->setChecked(true); break;
	case Steps::Canny : ui.radioCanny->setChecked(true); break;
	}
}

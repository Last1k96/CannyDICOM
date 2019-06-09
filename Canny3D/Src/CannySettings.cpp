#include "CannySettings.h"

CannySettings::CannySettings(QWidget *parent)
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

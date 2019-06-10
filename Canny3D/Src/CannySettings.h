#pragma once
#include <QWidget>
#include "Settings.h"
#include "ui_CannySettings.h"


class CannySettings : public QWidget
{
	Q_OBJECT

public:
	CannySettings(QWidget *parent = Q_NULLPTR);

public slots:
	void setVOICenterMinimum(int value);
	void setVOICenterMaximum(int value);
	void setVOIWidthMinimum(int value);
	void setVOIWidthMaximum(int value);
	void emitSettingsChanged();

signals:
	void settingsChanged(Settings const&);

public:
	[[nodiscard]] Settings currentSettings() const;
	void setUiValues(Settings const& s) const;

private:
	Ui::CannySettings ui;
};

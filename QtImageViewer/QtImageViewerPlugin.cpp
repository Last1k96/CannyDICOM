#include "QtImageViewer.h"
#include "QtImageViewerPlugin.h"

#include <QtCore/QtPlugin>

QtImageViewerPlugin::QtImageViewerPlugin(QObject *parent)
	: QObject(parent)
{
	initialized = false;
}

void QtImageViewerPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
	if (initialized)
		return;

	initialized = true;
}

bool QtImageViewerPlugin::isInitialized() const
{
	return initialized;
}

QWidget *QtImageViewerPlugin::createWidget(QWidget *parent)
{
	return new QtImageViewer(parent);
}

QString QtImageViewerPlugin::name() const
{
	return "QtImageViewer";
}

QString QtImageViewerPlugin::group() const
{
	return "My Plugins";
}

QIcon QtImageViewerPlugin::icon() const
{
	return QIcon();
}

QString QtImageViewerPlugin::toolTip() const
{
	return QString();
}

QString QtImageViewerPlugin::whatsThis() const
{
	return QString();
}

bool QtImageViewerPlugin::isContainer() const
{
	return false;
}

QString QtImageViewerPlugin::domXml() const
{
	return "<widget class=\"QtImageViewer\" name=\"qtImageViewer\">\n"
		" <property name=\"geometry\">\n"
		"  <rect>\n"
		"   <x>0</x>\n"
		"   <y>0</y>\n"
		"   <width>100</width>\n"
		"   <height>100</height>\n"
		"  </rect>\n"
		" </property>\n"
		"</widget>\n";
}

QString QtImageViewerPlugin::includeFile() const
{
	return "QtImageViewer.h";
}

#include "CannyImageViewer.h"
#include "CannyImageViewerPlugin.h"

#include <QtCore/QtPlugin>

CannyImageViewerPlugin::CannyImageViewerPlugin(QObject *parent)
	: QObject(parent)
{
	initialized = false;
}

void CannyImageViewerPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
	if (initialized)
		return;

	initialized = true;
}

bool CannyImageViewerPlugin::isInitialized() const
{
	return initialized;
}

QWidget *CannyImageViewerPlugin::createWidget(QWidget *parent)
{
	return new CannyImageViewer(parent);
}

QString CannyImageViewerPlugin::name() const
{
	return "CannyImageViewer";
}

QString CannyImageViewerPlugin::group() const
{
	return "My Plugins";
}

QIcon CannyImageViewerPlugin::icon() const
{
	return QIcon();
}

QString CannyImageViewerPlugin::toolTip() const
{
	return QString();
}

QString CannyImageViewerPlugin::whatsThis() const
{
	return QString();
}

bool CannyImageViewerPlugin::isContainer() const
{
	return false;
}

QString CannyImageViewerPlugin::domXml() const
{
	return "<widget class=\"CannyImageViewer\" name=\"cannyImageViewer\">\n"
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

QString CannyImageViewerPlugin::includeFile() const
{
	return "CannyImageViewer.h";
}

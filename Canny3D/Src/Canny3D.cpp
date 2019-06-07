#include "Canny3D.h"
#include <QFileDialog>
#include <QDialog>
#include <QImageReader>
#include <QImageWriter>
#include <qmessagebox.h>
#include <QAction>
#include "Utility.h"
#include "DicomViewer.h"
#include "QGLMeshViewer.h"

Canny3D::Canny3D(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.openAction, &QAction::triggered, this, &Canny3D::open);
	connect(ui.openFolderAction, &QAction::triggered, this, &Canny3D::openFolder);
}

bool Canny3D::loadFiles(const QString& fileName)
{
	try {
		images = loadData(fileName.toStdWString());
	}
	catch (std::exception& e)
	{
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
			tr("Cannot load %1: %2")
			.arg(QDir::toNativeSeparators(fileName),
				QString::fromStdString(e.what())));
		return false;
	}

	setWindowFilePath(fileName);

	return true;
}

void Canny3D::addNewTab() const
{
	auto tab = new QWidget();
	tab->setObjectName(QString::fromUtf8("tab"));
	auto verticalLayout = new QVBoxLayout(tab);
	verticalLayout->setSpacing(6);
	verticalLayout->setContentsMargins(11, 11, 11, 11);
	verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
	auto widget = new DicomViewer(tab, images);
	widget->setObjectName(QString::fromUtf8("widget"));
	QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
	sizePolicy3.setHorizontalStretch(0);
	sizePolicy3.setVerticalStretch(0);
	sizePolicy3.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
	widget->setSizePolicy(sizePolicy3);

	verticalLayout->addWidget(widget);

	auto horizontalSlider = new QSlider(tab);
	horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
	horizontalSlider->setOrientation(Qt::Horizontal);

	verticalLayout->addWidget(horizontalSlider);

	auto horizontalLayout_2 = new QHBoxLayout();
	horizontalLayout_2->setSpacing(0);
	horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
	horizontalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
	auto groupBox = new QGroupBox(tab);
	groupBox->setObjectName(QString::fromUtf8("groupBox"));
	QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	sizePolicy4.setHorizontalStretch(0);
	sizePolicy4.setVerticalStretch(0);
	sizePolicy4.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
	groupBox->setSizePolicy(sizePolicy4);
	groupBox->setMinimumSize(QSize(0, 150));

	horizontalLayout_2->addWidget(groupBox);

	auto verticalLayout_2 = new QVBoxLayout();
	verticalLayout_2->setSpacing(0);
	verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
	verticalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
	auto pushButton_2 = new QPushButton(tab);
	pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
	pushButton_2->setText(QString::fromWCharArray(L"Построить"));
	QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Preferred);
	sizePolicy5.setHorizontalStretch(0);
	sizePolicy5.setVerticalStretch(0);
	sizePolicy5.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
	pushButton_2->setSizePolicy(sizePolicy5);

	verticalLayout_2->addWidget(pushButton_2);

	horizontalLayout_2->addLayout(verticalLayout_2);

	verticalLayout->addLayout(horizontalLayout_2);

	horizontalSlider->setRange(0, images.size());
	connect(horizontalSlider, &QSlider::valueChanged, widget, &DicomViewer::selectImage);
	connect(widget, &DicomViewer::imageChanged, horizontalSlider, &QSlider::setValue);
	connect(pushButton_2, &QPushButton::pressed, this, &Canny3D::addNewTab3D);
	ui.tabWidget->addTab(tab, "Name");
}

void Canny3D::addNewTab3D() const
{
	auto tab = new QWidget();
	tab->setObjectName(QString::fromUtf8("tab3D"));

	auto widget = new QGLMeshViewer(tab);
	widget->setObjectName(QString::fromUtf8("widget"));
	ui.tabWidget->addTab(tab, "Name3D");

	auto verticalLayout = new QVBoxLayout(tab);
	verticalLayout->setSpacing(0);
	verticalLayout->addWidget(widget);
}



bool Canny3D::initiateOpenDialog(QString const& dialogName, QFileDialog::FileMode dialogType)
{
	QFileDialog dialog(this, dialogName);

	static bool firstDialog = true;
	if (firstDialog)
	{
		firstDialog = false;
		//dialog.setDirectory(QDir::currentPath());
		dialog.setDirectory(tr("d:/DICOM/Latishev-after1operation/DICOM"));
	}

	dialog.setFileMode(dialogType);

	return (dialog.exec() == QDialog::Accepted) && loadFiles(dialog.selectedFiles().first());
}

void Canny3D::open()
{
	auto const success = initiateOpenDialog(QString::fromWCharArray(L"Открыть файл"), QFileDialog::AnyFile);
	if (!success) return;
	addNewTab();
}

void Canny3D::updateTree()
{
	
}

void Canny3D::openFolder()
{
	auto const success = initiateOpenDialog(QString::fromWCharArray(L"Открыть папку"), QFileDialog::Directory);
	if (!success) return;
	updateTree();
	addNewTab();
}

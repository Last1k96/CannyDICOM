#include "Canny3D.h"
#include <QFileDialog>
#include <QDialog>
#include <QGroupBox>
#include <QImageWriter>
#include <qmessagebox.h>
#include <QAction>
#include "Utility.h"
#include "DicomViewer.h"
#include "QGLMeshViewer.h"
#include "DicomTreeItem.h"

Canny3D::Canny3D(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.tabWidget->removeTab(0);

	connect(ui.openAction, &QAction::triggered, this, &Canny3D::open);
	connect(ui.openFolderAction, &QAction::triggered, this, &Canny3D::openFolder);
	connect(ui.treeWidget, &QTreeWidget::expanded, this, &Canny3D::adjustColumns);
	connect(ui.treeWidget, &QTreeWidget::itemDoubleClicked, this, &Canny3D::addNewTab);
	connect(ui.tabWidget, &QTabWidget::tabCloseRequested, ui.tabWidget, &QTabWidget::removeTab);
}

std::vector<ImebraImage> Canny3D::loadFiles(const QString& fileName)
{
	auto images = std::vector<ImebraImage>{};
	try
	{
		images = loadData(fileName.toStdWString());
	}
	catch (std::exception& e)
	{
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
		                         tr("Cannot load %1: %2")
		                         .arg(QDir::toNativeSeparators(fileName),
		                              QString::fromStdString(e.what())));
		return {};
	}
	
	return images;
}

// Скопировал из ui_Canny3D
void Canny3D::addNewTab(QTreeWidgetItem* item, int column) const
{
	auto images = dynamic_cast<DicomTreeItem*>(item)->images;
	const auto count = images.size();
	if (count == 0) return;
	auto const tabName = QString::fromStdWString(images.front().tags.groupName[0])
		+ " (" + QString::fromStdWString(images.front().tags.groupName[2]) + ")";

	/// ui_Canny3D start
	auto tab = new QWidget();
	tab = new QWidget();
	auto horizontalLayout_2 = new QHBoxLayout(tab);
	horizontalLayout_2->setSpacing(6);
	horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
	auto splitter_2 = new QSplitter(tab);
	splitter_2->setOrientation(Qt::Vertical);
	auto layoutWidget = new QWidget(splitter_2);
	auto verticalLayout = new QVBoxLayout(layoutWidget);
	verticalLayout->setSpacing(6);
	verticalLayout->setContentsMargins(11, 11, 11, 11);
	verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
	verticalLayout->setContentsMargins(0, 0, 0, 0);
	auto viewer = new DicomViewer(tab, std::move(images)); // измененный конструктор
	QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	sizePolicy3.setHorizontalStretch(0);
	sizePolicy3.setVerticalStretch(0);
	sizePolicy3.setHeightForWidth(viewer->sizePolicy().hasHeightForWidth());
	viewer->setSizePolicy(sizePolicy3);

	verticalLayout->addWidget(viewer);

	auto horizontalLayout_3 = new QHBoxLayout();
	horizontalLayout_3->setSpacing(6);
	auto horizontalSlider = new QSlider(layoutWidget);
	QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
	sizePolicy4.setHorizontalStretch(0);
	sizePolicy4.setVerticalStretch(0);
	sizePolicy4.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
	horizontalSlider->setSizePolicy(sizePolicy4);
	horizontalSlider->setOrientation(Qt::Horizontal);
	horizontalSlider->setInvertedAppearance(false);
	horizontalSlider->setInvertedControls(false);

	horizontalLayout_3->addWidget(horizontalSlider);

	auto pushButton_2 = new QPushButton(layoutWidget);
	QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
	sizePolicy5.setHorizontalStretch(0);
	sizePolicy5.setVerticalStretch(0);
	sizePolicy5.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
	pushButton_2->setSizePolicy(sizePolicy5);
	pushButton_2->setMinimumSize(QSize(30, 30));
	pushButton_2->setMaximumSize(QSize(30, 30));
	QFont font;
	font.setPointSize(12);
	pushButton_2->setFont(font);
	pushButton_2->setCheckable(false);

	horizontalLayout_3->addWidget(pushButton_2);

	verticalLayout->addLayout(horizontalLayout_3);

	splitter_2->addWidget(layoutWidget);
	auto settings = new CannySettings(splitter_2);
	settings->setMinimumSize(QSize(0, 167));
	settings->setMaximumSize(QSize(16777215, 167));
	splitter_2->addWidget(settings);

	horizontalLayout_2->addWidget(splitter_2);
	/// ui_Canny3D end

	horizontalSlider->setRange(0, count - 1);
	pushButton_2->setText(QString::fromWCharArray(L"3D"));
	connect(horizontalSlider, &QSlider::valueChanged, viewer, &DicomViewer::selectImage);
	connect(viewer, &DicomViewer::imageChanged, horizontalSlider, &QSlider::setValue);
	connect(pushButton_2, &QPushButton::pressed, [this, viewer]()
	{
		auto& images = viewer->images;
		auto const tabName = QString::fromStdWString(images.front().tags.groupName[0])
			+ " (" + QString::fromStdWString(images.front().tags.groupName[2]) + ") 3D";
		
		// convert to cv::Mat
		auto edges = std::vector<cv::Mat>(images.size());
#pragma omp parallel for
		for (int i = 0; i < images.size(); i++)
		{
			edges[i] = viewer->computeImage(i, true);
		}

		// get size in mm
		auto const& image = images[0].image;

		auto sizeInMillimeters = std::tuple
		{
			image->getWidthMm() / image->getWidth(),
			image->getHeightMm() / image->getHeight(),
			std::fabs(images[0].tags.sliceLocation - images[1].tags.sliceLocation)
		};

		this->addNewTab3D(std::move(edges), sizeInMillimeters, tabName);
	});
	connect(settings, &CannySettings::settingsChanged, viewer, &DicomViewer::setSettings);
	ui.tabWidget->addTab(tab, tabName);

	// updateUI
	if (viewer->images.empty()) return;
	auto const& image = viewer->images[0];
	auto s = Settings();
	s.voiCenter = (image.voi) ? image.voi->center : 300;
	s.voiWidth = (image.voi) ? image.voi->width : 2500;
	s.gaussKernel = 5;
	s.gaussSigma = 1.0;
	s.cannyLow = 80;
	s.cannyHigh = 220;
	s.step = Steps::VOI;
	settings->setUiValues(s);
}

void Canny3D::addNewTab3D(std::vector<cv::Mat> images, std::tuple<double, double, double> xyzInMillimeters, QString const& tabName) const
{
	auto tab = new QWidget();
	auto widget = new QGLMeshViewer(tab, std::move(images));
	ui.tabWidget->addTab(tab, tabName);

	auto verticalLayout = new QVBoxLayout(tab);
	verticalLayout->setSpacing(0);
	verticalLayout->addWidget(widget);
}

void Canny3D::adjustColumns(QModelIndex const& index)
{
	for (auto i = 0; i < ui.treeWidget->columnCount(); ++i)
	{
		ui.treeWidget->resizeColumnToContents(i);
	}
}


std::optional<std::vector<ImebraImage>> Canny3D::initiateOpenDialog(QString const& name, QFileDialog::FileMode type)
{
	QFileDialog dialog(this, name);

	static bool firstDialog = true;
	if (firstDialog)
	{
		firstDialog = false;
		//dialog.setDirectory(QDir::currentPath());
		dialog.setDirectory(tr("d:/DICOM/Latishev-after1operation/DICOM"));
	}
	dialog.setFileMode(type);

	if (dialog.exec() != QDialog::Accepted) return {};
	return loadFiles(dialog.selectedFiles().first());
}

void Canny3D::open()
{
	auto images = initiateOpenDialog(QString::fromWCharArray(L"Открыть файл"), QFileDialog::AnyFile);
	if (images)	updateTree(std::move(*images));
}

void Canny3D::openFolder()
{
	auto images = initiateOpenDialog(QString::fromWCharArray(L"Открыть папку"), QFileDialog::Directory);
	if (images)	updateTree(std::move(*images));
}

using It = std::vector<ImebraImage>::iterator;

static void createTree(QTreeWidgetItem* parent, It begin, It end, int tagId = 0)
{
	if (tagId == 3)
	{
		return;
	}

	std::stable_sort(begin, end, [&](ImebraImage const& lhs, ImebraImage const& rhs)
	{
		return lhs.tags.groupBy[tagId] < rhs.tags.groupBy[tagId];
	});

	auto right = begin;
	while (right != end)
	{
		auto left = right;
		right = std::lower_bound(left, end, *left, [&](ImebraImage const& lhs, ImebraImage const& rhs)
		{
			return lhs.tags.groupBy[tagId] == rhs.tags.groupBy[tagId];
		});

		auto child = [&]
		{
			if (tagId < 2) return new DicomTreeItem(parent, left, left);

			std::sort(left, right, [](ImebraImage const& lhs, ImebraImage const& rhs)
			{
				return lhs.tags.sliceLocation < rhs.tags.sliceLocation;
			});
			return new DicomTreeItem(parent, left, right);
		}();

		if (tagId == 0)
		{
			child->setIcon(0, QIcon("Resources/patient.ico"));
			child->setToolTip(0, QString::fromWCharArray(L"Пациент"));
		}
		else if (tagId == 1)
		{
			child->setIcon(0, QIcon("Resources/study.ico"));
			child->setToolTip(0, QString::fromWCharArray(L"Исследование"));
		}
		else if (tagId == 2)
		{
			child->setIcon(0, QIcon("Resources/series.ico"));
			child->setToolTip(0, QString::fromWCharArray(L"Изображения"));
		}
		child->setText(0, QString::fromStdWString(left->tags.groupName[tagId]));
		createTree(child, left, right, tagId + 1);
	}
}

void Canny3D::updateTree(std::vector<ImebraImage>&& images)
{
	auto tree = ui.treeWidget;
	tree->clear();
	auto root = tree->invisibleRootItem();

	createTree(root, begin(images), end(images));

	for (auto i = 0; i < tree->topLevelItemCount(); ++i)
	{
		auto patient = tree->topLevelItem(i);
		for (auto j = 0; j < patient->childCount(); ++j)
		{
			auto study = patient->child(j);
			auto str = std::wstring(L"(") + std::to_wstring(study->childCount()) + L": серии)";
			study->setText(0, study->text(0) + QString::fromStdWString(str));
		}
	}

	auto model = tree->model();
	auto indexes = model->match(model->index(0, 0), Qt::DisplayRole, "*", -1, Qt::MatchWildcard | Qt::MatchRecursive);
	foreach(QModelIndex index, indexes)
		tree->expand(index);

	for (auto i = 0; i < tree->columnCount(); ++i)
	{
		tree->resizeColumnToContents(i);
	}
}

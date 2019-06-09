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
#include "DicomTreeItem.h"
#include <fstream>

Canny3D::Canny3D(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

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

	//setWindowFilePath(fileName);

	return images;
}

void Canny3D::addNewTab(QTreeWidgetItem* item, int column) const
{
	auto images = dynamic_cast<DicomTreeItem*>(item)->images;
	const auto count = images.size();
	if (count == 0) return;
	auto const tabName = QString::fromStdWString(images.front().tags.groupName[0])
		+ " (" + QString::fromStdWString(images.front().tags.groupName[2]) + ")";

	auto tab = new QWidget();
	tab->setObjectName(QString::fromUtf8("tab"));
	auto verticalLayout = new QVBoxLayout(tab);
	verticalLayout->setSpacing(6);
	verticalLayout->setContentsMargins(11, 11, 11, 11);
	verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
	auto widget = new DicomViewer(tab, std::move(images));
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

	horizontalSlider->setRange(0, count - 1);
	connect(horizontalSlider, &QSlider::valueChanged, widget, &DicomViewer::selectImage);
	connect(widget, &DicomViewer::imageChanged, horizontalSlider, &QSlider::setValue);
	connect(pushButton_2, &QPushButton::pressed, [this, widget]()
	{
		this->addNewTab3D(widget->images);
	});

	ui.tabWidget->addTab(tab, tabName);
}

void Canny3D::addNewTab3D(std::vector<ImebraImage> const& images) const
{
	auto tab = new QWidget();
	tab->setObjectName(QString::fromUtf8("tab3D"));

	auto widget = new QGLMeshViewer(tab);
	widget->setObjectName(QString::fromUtf8("widget"));
	auto const tabName = QString::fromStdWString(images.front().tags.groupName[0])
		+ " (" + QString::fromStdWString(images.front().tags.groupName[2]) + ") 3D";

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
	if (images)
		updateTree(std::move(*images));
	//addNewTab(std::move(images));
}

void Canny3D::openFolder()
{
	auto images = initiateOpenDialog(QString::fromWCharArray(L"Открыть папку"), QFileDialog::Directory);
	if (images)
		updateTree(std::move(*images));
	//addNewTab(std::move(images));
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

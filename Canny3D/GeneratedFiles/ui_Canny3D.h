/********************************************************************************
** Form generated from reading UI file 'Canny3D.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANNY3D_H
#define UI_CANNY3D_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "CannySettings.h"
#include "DicomViewer.h"

QT_BEGIN_NAMESPACE

class Ui_Canny3DClass
{
public:
    QAction *openAction;
    QAction *openFolderAction;
    QAction *exitAction;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTreeWidget *treeWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_3;
    QSplitter *splitter_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    DicomViewer *widget1;
    QSlider *horizontalSlider;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_2;
    CannySettings *widget_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *Canny3DClass)
    {
        if (Canny3DClass->objectName().isEmpty())
            Canny3DClass->setObjectName(QString::fromUtf8("Canny3DClass"));
        Canny3DClass->resize(859, 434);
        Canny3DClass->setBaseSize(QSize(800, 600));
        Canny3DClass->setWindowOpacity(1.000000000000000);
        Canny3DClass->setTabShape(QTabWidget::Rounded);
        openAction = new QAction(Canny3DClass);
        openAction->setObjectName(QString::fromUtf8("openAction"));
        openFolderAction = new QAction(Canny3DClass);
        openFolderAction->setObjectName(QString::fromUtf8("openFolderAction"));
        exitAction = new QAction(Canny3DClass);
        exitAction->setObjectName(QString::fromUtf8("exitAction"));
        centralWidget = new QWidget(Canny3DClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        treeWidget = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setColumnCount(1);
        splitter->addWidget(treeWidget);
        treeWidget->header()->setVisible(false);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(8);
        sizePolicy1.setVerticalStretch(8);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setTabsClosable(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_3 = new QHBoxLayout(tab);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        splitter_2 = new QSplitter(tab);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        widget = new QWidget(splitter_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget1 = new DicomViewer(widget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget1->sizePolicy().hasHeightForWidth());
        widget1->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(widget1);

        horizontalSlider = new QSlider(widget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);

        splitter_2->addWidget(widget);
        widget2 = new QWidget(splitter_2);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        horizontalLayout_2 = new QHBoxLayout(widget2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_2 = new CannySettings(widget2);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy3);
        widget_2->setMinimumSize(QSize(0, 250));

        horizontalLayout_2->addWidget(widget_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout_2->addItem(verticalSpacer);

        pushButton_2 = new QPushButton(widget2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy4);
        pushButton_2->setMinimumSize(QSize(0, 0));
        pushButton_2->setCheckable(false);

        verticalLayout_2->addWidget(pushButton_2);


        horizontalLayout_2->addLayout(verticalLayout_2);

        splitter_2->addWidget(widget2);

        horizontalLayout_3->addWidget(splitter_2);

        tabWidget->addTab(tab, QString());
        splitter->addWidget(tabWidget);

        horizontalLayout->addWidget(splitter);

        Canny3DClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Canny3DClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 859, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        Canny3DClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Canny3DClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Canny3DClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(openAction);
        menu->addAction(openFolderAction);
        menu->addSeparator();
        menu->addAction(exitAction);

        retranslateUi(Canny3DClass);
        QObject::connect(exitAction, SIGNAL(triggered()), Canny3DClass, SLOT(close()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Canny3DClass);
    } // setupUi

    void retranslateUi(QMainWindow *Canny3DClass)
    {
        Canny3DClass->setWindowTitle(QApplication::translate("Canny3DClass", "Canny3D", nullptr));
        openAction->setText(QApplication::translate("Canny3DClass", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        openFolderAction->setText(QApplication::translate("Canny3DClass", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\277\320\260\320\277\320\272\321\203", nullptr));
        exitAction->setText(QApplication::translate("Canny3DClass", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        pushButton_2->setText(QApplication::translate("Canny3DClass", "\320\240\320\260\321\201\321\207\320\270\321\202\320\260\321\202\321\214 3D \320\277\320\276\320\262\320\265\321\200\321\205\320\275\320\276\321\201\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Canny3DClass", "Tab 1", nullptr));
        menu->setTitle(QApplication::translate("Canny3DClass", "\320\244\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Canny3DClass: public Ui_Canny3DClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANNY3D_H

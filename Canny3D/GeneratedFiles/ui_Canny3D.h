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
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

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
    QTreeView *treeView;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *Canny3DClass)
    {
        if (Canny3DClass->objectName().isEmpty())
            Canny3DClass->setObjectName(QString::fromUtf8("Canny3DClass"));
        Canny3DClass->resize(572, 368);
        Canny3DClass->setBaseSize(QSize(800, 600));
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
        splitter->setLineWidth(1);
        splitter->setOrientation(Qt::Horizontal);
        treeView = new QTreeView(splitter);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy1);
        splitter->addWidget(treeView);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(8);
        sizePolicy2.setVerticalStretch(8);
        sizePolicy2.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy2);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        splitter->addWidget(tabWidget);

        horizontalLayout->addWidget(splitter);

        Canny3DClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Canny3DClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 572, 21));
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

        QMetaObject::connectSlotsByName(Canny3DClass);
    } // setupUi

    void retranslateUi(QMainWindow *Canny3DClass)
    {
        Canny3DClass->setWindowTitle(QApplication::translate("Canny3DClass", "Canny3D", nullptr));
        openAction->setText(QApplication::translate("Canny3DClass", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        openFolderAction->setText(QApplication::translate("Canny3DClass", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\277\320\260\320\277\320\272\321\203", nullptr));
        exitAction->setText(QApplication::translate("Canny3DClass", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Canny3DClass", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Canny3DClass", "Tab 2", nullptr));
        menu->setTitle(QApplication::translate("Canny3DClass", "\320\244\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Canny3DClass: public Ui_Canny3DClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANNY3D_H

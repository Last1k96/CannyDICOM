/********************************************************************************
** Form generated from reading UI file 'QtGuiDicomViewer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIDICOMVIEWER_H
#define UI_QTGUIDICOMVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiDicomViewerClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *QtGuiDicomViewerClass)
    {
        if (QtGuiDicomViewerClass->objectName().isEmpty())
            QtGuiDicomViewerClass->setObjectName(QString::fromUtf8("QtGuiDicomViewerClass"));
        QtGuiDicomViewerClass->resize(774, 567);
        centralWidget = new QWidget(QtGuiDicomViewerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QtGuiDicomViewerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtGuiDicomViewerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 774, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        QtGuiDicomViewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtGuiDicomViewerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtGuiDicomViewerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtGuiDicomViewerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtGuiDicomViewerClass->setStatusBar(statusBar);
        toolBar = new QToolBar(QtGuiDicomViewerClass);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        QtGuiDicomViewerClass->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menu->menuAction());

        retranslateUi(QtGuiDicomViewerClass);

        QMetaObject::connectSlotsByName(QtGuiDicomViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiDicomViewerClass)
    {
        QtGuiDicomViewerClass->setWindowTitle(QApplication::translate("QtGuiDicomViewerClass", "QtGuiDicomViewer", nullptr));
        menu->setTitle(QApplication::translate("QtGuiDicomViewerClass", "\320\244\320\260\320\271\320\273", nullptr));
        toolBar->setWindowTitle(QApplication::translate("QtGuiDicomViewerClass", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGuiDicomViewerClass: public Ui_QtGuiDicomViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIDICOMVIEWER_H

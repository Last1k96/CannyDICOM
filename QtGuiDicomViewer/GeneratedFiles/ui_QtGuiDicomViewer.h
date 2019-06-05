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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiDicomViewerClass
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *imageLabel;
    QScrollBar *horizontalScrollBar;
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
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(240, 100, 441, 291));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        imageLabel = new QLabel(widget);
        imageLabel->setObjectName(QString::fromUtf8("imageLabel"));

        verticalLayout->addWidget(imageLabel);

        horizontalScrollBar = new QScrollBar(widget);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalScrollBar);

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
        imageLabel->setText(QString());
        menu->setTitle(QApplication::translate("QtGuiDicomViewerClass", "\320\244\320\260\320\271\320\273", nullptr));
        toolBar->setWindowTitle(QApplication::translate("QtGuiDicomViewerClass", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGuiDicomViewerClass: public Ui_QtGuiDicomViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIDICOMVIEWER_H

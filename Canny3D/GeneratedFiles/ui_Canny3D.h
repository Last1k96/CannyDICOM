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
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include "QGLMeshViewer.h"

QT_BEGIN_NAMESPACE

class Ui_Canny3DClass
{
public:
    QGLMeshViewer *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *Canny3DClass)
    {
        if (Canny3DClass->objectName().isEmpty())
            Canny3DClass->setObjectName(QString::fromUtf8("Canny3DClass"));
        Canny3DClass->resize(600, 400);
        centralWidget = new QGLMeshViewer(Canny3DClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        Canny3DClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Canny3DClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        Canny3DClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Canny3DClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Canny3DClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(Canny3DClass);

        QMetaObject::connectSlotsByName(Canny3DClass);
    } // setupUi

    void retranslateUi(QMainWindow *Canny3DClass)
    {
        Canny3DClass->setWindowTitle(QApplication::translate("Canny3DClass", "Canny3D", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Canny3DClass: public Ui_Canny3DClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANNY3D_H

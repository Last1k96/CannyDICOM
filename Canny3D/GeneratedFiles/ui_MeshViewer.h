/********************************************************************************
** Form generated from reading UI file 'MeshViewer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESHVIEWER_H
#define UI_MESHVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include "QGLMeshViewer.h"

QT_BEGIN_NAMESPACE

class Ui_MeshViewer
{
public:
    QHBoxLayout *horizontalLayout;
    QGLMeshViewer *widget;

    void setupUi(QWidget *MeshViewer)
    {
        if (MeshViewer->objectName().isEmpty())
            MeshViewer->setObjectName(QString::fromUtf8("MeshViewer"));
        MeshViewer->resize(588, 449);
        horizontalLayout = new QHBoxLayout(MeshViewer);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QGLMeshViewer(MeshViewer);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout->addWidget(widget);


        retranslateUi(MeshViewer);

        QMetaObject::connectSlotsByName(MeshViewer);
    } // setupUi

    void retranslateUi(QWidget *MeshViewer)
    {
        MeshViewer->setWindowTitle(QApplication::translate("MeshViewer", "MeshViewer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MeshViewer: public Ui_MeshViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHVIEWER_H

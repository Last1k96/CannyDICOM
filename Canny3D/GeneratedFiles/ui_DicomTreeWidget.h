/********************************************************************************
** Form generated from reading UI file 'DicomTreeWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DICOMTREEWIDGET_H
#define UI_DICOMTREEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_DicomTreeWidget
{
public:

    void setupUi(QTreeWidget *DicomTreeWidget)
    {
        if (DicomTreeWidget->objectName().isEmpty())
            DicomTreeWidget->setObjectName(QString::fromUtf8("DicomTreeWidget"));
        DicomTreeWidget->resize(400, 300);
        if (DicomTreeWidget->header()->objectName().isEmpty())

        retranslateUi(DicomTreeWidget);

        QMetaObject::connectSlotsByName(DicomTreeWidget);
    } // setupUi

    void retranslateUi(QTreeWidget *DicomTreeWidget)
    {
        DicomTreeWidget->setWindowTitle(QApplication::translate("DicomTreeWidget", "DicomTreeWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DicomTreeWidget: public Ui_DicomTreeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DICOMTREEWIDGET_H

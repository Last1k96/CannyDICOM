/********************************************************************************
** Form generated from reading UI file 'CannySettings.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANNYSETTINGS_H
#define UI_CANNYSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CannySettings
{
public:
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;

    void setupUi(QWidget *CannySettings)
    {
        if (CannySettings->objectName().isEmpty())
            CannySettings->setObjectName(QString::fromUtf8("CannySettings"));
        CannySettings->resize(591, 248);
        horizontalLayout = new QHBoxLayout(CannySettings);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        stackedWidget = new QStackedWidget(CannySettings);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        horizontalLayout_2 = new QHBoxLayout(page_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox = new QGroupBox(page_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));

        horizontalLayout_2->addWidget(groupBox);

        stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(stackedWidget);


        retranslateUi(CannySettings);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(CannySettings);
    } // setupUi

    void retranslateUi(QWidget *CannySettings)
    {
        CannySettings->setWindowTitle(QApplication::translate("CannySettings", "CannySettings", nullptr));
        groupBox->setTitle(QApplication::translate("CannySettings", "\320\244\320\270\320\273\321\214\321\202\321\200 \320\223\320\260\321\203\321\201\321\201\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CannySettings: public Ui_CannySettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANNYSETTINGS_H

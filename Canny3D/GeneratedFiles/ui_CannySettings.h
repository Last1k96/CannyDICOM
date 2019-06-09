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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CannySettings
{
public:
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QSpinBox *centerVal;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QSpinBox *centerMin;
    QLabel *label_7;
    QSlider *centerSlider;
    QVBoxLayout *verticalLayout_4;
    QSpinBox *centerMax;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QSpinBox *widthVal;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QSpinBox *widthMin;
    QLabel *label_9;
    QSlider *widthSlider;
    QVBoxLayout *verticalLayout_6;
    QSpinBox *widthMax;
    QLabel *label_10;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QSpinBox *spinBox;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QLabel *label_6;
    QLineEdit *lineEdit_4;

    void setupUi(QWidget *CannySettings)
    {
        if (CannySettings->objectName().isEmpty())
            CannySettings->setObjectName(QString::fromUtf8("CannySettings"));
        CannySettings->resize(829, 398);
        groupBox = new QGroupBox(CannySettings);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 571, 181));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        horizontalLayout_7 = new QHBoxLayout(groupBox);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(6, 6, 6, 6);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        centerVal = new QSpinBox(groupBox);
        centerVal->setObjectName(QString::fromUtf8("centerVal"));
        centerVal->setMinimum(0);
        centerVal->setSingleStep(5);
        centerVal->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);

        horizontalLayout_5->addWidget(centerVal);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        centerMin = new QSpinBox(groupBox);
        centerMin->setObjectName(QString::fromUtf8("centerMin"));
        centerMin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        centerMin->setMinimum(-65535);
        centerMin->setMaximum(65536);

        verticalLayout->addWidget(centerMin);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_7);


        horizontalLayout->addLayout(verticalLayout);

        centerSlider = new QSlider(groupBox);
        centerSlider->setObjectName(QString::fromUtf8("centerSlider"));
        centerSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(centerSlider);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetMinimumSize);
        centerMax = new QSpinBox(groupBox);
        centerMax->setObjectName(QString::fromUtf8("centerMax"));
        centerMax->setButtonSymbols(QAbstractSpinBox::NoButtons);
        centerMax->setMinimum(-65535);
        centerMax->setMaximum(65536);

        verticalLayout_4->addWidget(centerMax);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_8);


        horizontalLayout->addLayout(verticalLayout_4);


        verticalLayout_7->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_6->addWidget(label_2);

        widthVal = new QSpinBox(groupBox);
        widthVal->setObjectName(QString::fromUtf8("widthVal"));

        horizontalLayout_6->addWidget(widthVal);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_7->addLayout(horizontalLayout_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetFixedSize);
        widthMin = new QSpinBox(groupBox);
        widthMin->setObjectName(QString::fromUtf8("widthMin"));
        widthMin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        widthMin->setMinimum(-65535);
        widthMin->setMaximum(65536);

        verticalLayout_5->addWidget(widthMin);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_9);


        horizontalLayout_4->addLayout(verticalLayout_5);

        widthSlider = new QSlider(groupBox);
        widthSlider->setObjectName(QString::fromUtf8("widthSlider"));
        widthSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(widthSlider);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setSizeConstraint(QLayout::SetMinimumSize);
        widthMax = new QSpinBox(groupBox);
        widthMax->setObjectName(QString::fromUtf8("widthMax"));
        widthMax->setButtonSymbols(QAbstractSpinBox::NoButtons);
        widthMax->setMinimum(-65535);
        widthMax->setMaximum(65536);

        verticalLayout_6->addWidget(widthMax);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_10);


        horizontalLayout_4->addLayout(verticalLayout_6);


        verticalLayout_7->addLayout(horizontalLayout_4);


        horizontalLayout_7->addLayout(verticalLayout_7);

        groupBox_2 = new QGroupBox(CannySettings);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(600, 130, 131, 119));
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        spinBox = new QSpinBox(groupBox_2);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        verticalLayout_2->addWidget(spinBox);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        doubleSpinBox = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setMaximum(1.000000000000000);
        doubleSpinBox->setSingleStep(0.050000000000000);
        doubleSpinBox->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
        doubleSpinBox->setValue(1.000000000000000);

        verticalLayout_2->addWidget(doubleSpinBox);


        horizontalLayout_2->addLayout(verticalLayout_2);

        groupBox_3 = new QGroupBox(CannySettings);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(590, 10, 131, 119));
        groupBox_3->setFlat(false);
        groupBox_3->setCheckable(false);
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_3->addWidget(label_5);

        lineEdit_3 = new QLineEdit(groupBox_3);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        sizePolicy.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy);
        lineEdit_3->setMinimumSize(QSize(20, 0));

        verticalLayout_3->addWidget(lineEdit_3);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_3->addWidget(label_6);

        lineEdit_4 = new QLineEdit(groupBox_3);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        sizePolicy.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy);
        lineEdit_4->setMinimumSize(QSize(20, 0));

        verticalLayout_3->addWidget(lineEdit_4);


        horizontalLayout_3->addLayout(verticalLayout_3);


        retranslateUi(CannySettings);
        QObject::connect(centerMin, SIGNAL(valueChanged(int)), CannySettings, SLOT(setVOICenterMinimum(int)));
        QObject::connect(centerMax, SIGNAL(valueChanged(int)), CannySettings, SLOT(setVOICenterMaximum(int)));
        QObject::connect(widthMin, SIGNAL(valueChanged(int)), CannySettings, SLOT(setVOIWidthMinimum(int)));
        QObject::connect(widthMax, SIGNAL(valueChanged(int)), CannySettings, SLOT(setVOIWidthMaximum(int)));
        QObject::connect(centerSlider, SIGNAL(valueChanged(int)), centerVal, SLOT(setValue(int)));
        QObject::connect(centerVal, SIGNAL(valueChanged(int)), centerSlider, SLOT(setValue(int)));
        QObject::connect(widthVal, SIGNAL(valueChanged(int)), widthSlider, SLOT(setValue(int)));
        QObject::connect(widthSlider, SIGNAL(valueChanged(int)), widthVal, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(CannySettings);
    } // setupUi

    void retranslateUi(QWidget *CannySettings)
    {
        CannySettings->setWindowTitle(QApplication::translate("CannySettings", "CannySettings", nullptr));
        groupBox->setTitle(QApplication::translate("CannySettings", "VOI \320\277\321\200\320\265\320\276\320\261\321\200\320\260\320\267\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        label->setText(QApplication::translate("CannySettings", "Window Center", nullptr));
        label_7->setText(QApplication::translate("CannySettings", "\320\234\320\270\320\275\320\270\320\274\321\203\320\274", nullptr));
        label_8->setText(QApplication::translate("CannySettings", "\320\234\320\260\320\272\321\201\320\270\320\274\321\203\320\274", nullptr));
        label_2->setText(QApplication::translate("CannySettings", "Window Width", nullptr));
        label_9->setText(QApplication::translate("CannySettings", "\320\234\320\270\320\275\320\270\320\274\321\203\320\274", nullptr));
        label_10->setText(QApplication::translate("CannySettings", "\320\234\320\260\320\272\321\201\320\270\320\274\321\203\320\274", nullptr));
        groupBox_2->setTitle(QApplication::translate("CannySettings", "\320\240\320\260\320\267\320\274\321\213\321\202\320\270\320\265 \320\223\320\260\321\203\321\201\321\201\320\260", nullptr));
        label_3->setText(QApplication::translate("CannySettings", "\320\240\320\260\320\267\320\274\320\265\321\200 \321\217\320\264\321\200\320\260 \321\201\320\262\321\221\321\200\321\202\320\272\320\270", nullptr));
        label_4->setText(QApplication::translate("CannySettings", "\320\241\320\270\320\263\320\274\320\260", nullptr));
        groupBox_3->setTitle(QApplication::translate("CannySettings", "\320\237\320\276\321\200\320\276\320\263 Canny", nullptr));
        label_5->setText(QApplication::translate("CannySettings", "Window Center", nullptr));
        label_6->setText(QApplication::translate("CannySettings", "Window Width", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CannySettings: public Ui_CannySettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANNYSETTINGS_H

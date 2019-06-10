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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CannySettings
{
public:
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioVoi;
    QRadioButton *radioGauss;
    QRadioButton *radioCanny;
    QPushButton *defaultButton;
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
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *formLayout;
    QLabel *label_3;
    QSpinBox *gaussKernel;
    QLabel *label_4;
    QDoubleSpinBox *gaussSigma;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QFormLayout *formLayout_2;
    QLabel *label_5;
    QSpinBox *cannyLow;
    QLabel *label_6;
    QSpinBox *cannyHigh;

    void setupUi(QWidget *CannySettings)
    {
        if (CannySettings->objectName().isEmpty())
            CannySettings->setObjectName(QString::fromUtf8("CannySettings"));
        CannySettings->resize(722, 167);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CannySettings->sizePolicy().hasHeightForWidth());
        CannySettings->setSizePolicy(sizePolicy);
        CannySettings->setMaximumSize(QSize(16777215, 16666666));
        horizontalLayout_8 = new QHBoxLayout(CannySettings);
        horizontalLayout_8->setSpacing(3);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(3, 0, 3, 3);
        groupBox_4 = new QGroupBox(CannySettings);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_2 = new QVBoxLayout(groupBox_4);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        radioVoi = new QRadioButton(groupBox_4);
        radioVoi->setObjectName(QString::fromUtf8("radioVoi"));
        radioVoi->setChecked(true);

        verticalLayout_2->addWidget(radioVoi);

        radioGauss = new QRadioButton(groupBox_4);
        radioGauss->setObjectName(QString::fromUtf8("radioGauss"));

        verticalLayout_2->addWidget(radioGauss);

        radioCanny = new QRadioButton(groupBox_4);
        radioCanny->setObjectName(QString::fromUtf8("radioCanny"));
        radioCanny->setChecked(false);

        verticalLayout_2->addWidget(radioCanny);

        defaultButton = new QPushButton(groupBox_4);
        defaultButton->setObjectName(QString::fromUtf8("defaultButton"));

        verticalLayout_2->addWidget(defaultButton);


        horizontalLayout_8->addWidget(groupBox_4);

        groupBox = new QGroupBox(CannySettings);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        horizontalLayout_7 = new QHBoxLayout(groupBox);
        horizontalLayout_7->setSpacing(3);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_7->setContentsMargins(3, 3, 3, 3);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(3);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(6, 0, 6, 0);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(label);

        centerVal = new QSpinBox(groupBox);
        centerVal->setObjectName(QString::fromUtf8("centerVal"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(centerVal->sizePolicy().hasHeightForWidth());
        centerVal->setSizePolicy(sizePolicy2);
        centerVal->setAccelerated(true);
        centerVal->setMinimum(0);
        centerVal->setSingleStep(1);
        centerVal->setStepType(QAbstractSpinBox::DefaultStepType);

        horizontalLayout_5->addWidget(centerVal);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(6, 0, 6, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        centerMin = new QSpinBox(groupBox);
        centerMin->setObjectName(QString::fromUtf8("centerMin"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(centerMin->sizePolicy().hasHeightForWidth());
        centerMin->setSizePolicy(sizePolicy3);
        centerMin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        centerMin->setMinimum(-65535);
        centerMin->setMaximum(65536);

        verticalLayout->addWidget(centerMin);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_7);


        horizontalLayout->addLayout(verticalLayout);

        centerSlider = new QSlider(groupBox);
        centerSlider->setObjectName(QString::fromUtf8("centerSlider"));
        sizePolicy1.setHeightForWidth(centerSlider->sizePolicy().hasHeightForWidth());
        centerSlider->setSizePolicy(sizePolicy1);
        centerSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(centerSlider);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_4->setContentsMargins(3, 3, 3, 3);
        centerMax = new QSpinBox(groupBox);
        centerMax->setObjectName(QString::fromUtf8("centerMax"));
        sizePolicy3.setHeightForWidth(centerMax->sizePolicy().hasHeightForWidth());
        centerMax->setSizePolicy(sizePolicy3);
        centerMax->setButtonSymbols(QAbstractSpinBox::NoButtons);
        centerMax->setMinimum(-65535);
        centerMax->setMaximum(65536);

        verticalLayout_4->addWidget(centerMax);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy2.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy2);
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_8);


        horizontalLayout->addLayout(verticalLayout_4);


        verticalLayout_7->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(6, -1, 6, -1);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(label_2);

        widthVal = new QSpinBox(groupBox);
        widthVal->setObjectName(QString::fromUtf8("widthVal"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(widthVal->sizePolicy().hasHeightForWidth());
        widthVal->setSizePolicy(sizePolicy4);
        widthVal->setAccelerated(true);
        widthVal->setStepType(QAbstractSpinBox::DefaultStepType);

        horizontalLayout_6->addWidget(widthVal);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_7->addLayout(horizontalLayout_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_4->setContentsMargins(6, 0, 6, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_5->setContentsMargins(3, 3, 3, 3);
        widthMin = new QSpinBox(groupBox);
        widthMin->setObjectName(QString::fromUtf8("widthMin"));
        sizePolicy3.setHeightForWidth(widthMin->sizePolicy().hasHeightForWidth());
        widthMin->setSizePolicy(sizePolicy3);
        widthMin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        widthMin->setMinimum(-65535);
        widthMin->setMaximum(65536);

        verticalLayout_5->addWidget(widthMin);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy2.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy2);
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_9);


        horizontalLayout_4->addLayout(verticalLayout_5);

        widthSlider = new QSlider(groupBox);
        widthSlider->setObjectName(QString::fromUtf8("widthSlider"));
        sizePolicy1.setHeightForWidth(widthSlider->sizePolicy().hasHeightForWidth());
        widthSlider->setSizePolicy(sizePolicy1);
        widthSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(widthSlider);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(3);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_6->setContentsMargins(3, 3, 3, 3);
        widthMax = new QSpinBox(groupBox);
        widthMax->setObjectName(QString::fromUtf8("widthMax"));
        sizePolicy3.setHeightForWidth(widthMax->sizePolicy().hasHeightForWidth());
        widthMax->setSizePolicy(sizePolicy3);
        widthMax->setButtonSymbols(QAbstractSpinBox::NoButtons);
        widthMax->setMinimum(-65535);
        widthMax->setMaximum(65536);

        verticalLayout_6->addWidget(widthMax);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy2.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy2);
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_10);


        horizontalLayout_4->addLayout(verticalLayout_6);


        verticalLayout_7->addLayout(horizontalLayout_4);


        horizontalLayout_7->addLayout(verticalLayout_7);


        horizontalLayout_8->addWidget(groupBox);

        widget = new QWidget(CannySettings);
        widget->setObjectName(QString::fromUtf8("widget"));
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2->setContentsMargins(3, 3, 3, 3);
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        formLayout->setContentsMargins(6, 6, 6, 6);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        gaussKernel = new QSpinBox(groupBox_2);
        gaussKernel->setObjectName(QString::fromUtf8("gaussKernel"));
        sizePolicy.setHeightForWidth(gaussKernel->sizePolicy().hasHeightForWidth());
        gaussKernel->setSizePolicy(sizePolicy);
        gaussKernel->setMaximumSize(QSize(16777215, 16777215));
        gaussKernel->setMinimum(1);
        gaussKernel->setMaximum(15);
        gaussKernel->setSingleStep(2);
        gaussKernel->setValue(5);

        formLayout->setWidget(0, QFormLayout::FieldRole, gaussKernel);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_4);

        gaussSigma = new QDoubleSpinBox(groupBox_2);
        gaussSigma->setObjectName(QString::fromUtf8("gaussSigma"));
        sizePolicy.setHeightForWidth(gaussSigma->sizePolicy().hasHeightForWidth());
        gaussSigma->setSizePolicy(sizePolicy);
        gaussSigma->setMaximumSize(QSize(16777215, 16777215));
        gaussSigma->setMaximum(5.000000000000000);
        gaussSigma->setSingleStep(0.050000000000000);
        gaussSigma->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
        gaussSigma->setValue(1.000000000000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, gaussSigma);


        horizontalLayout_2->addLayout(formLayout);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setFlat(false);
        groupBox_3->setCheckable(false);
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setSpacing(3);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_3->setContentsMargins(3, 3, 3, 3);
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        formLayout_2->setContentsMargins(6, 6, 6, 6);
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_5);

        cannyLow = new QSpinBox(groupBox_3);
        cannyLow->setObjectName(QString::fromUtf8("cannyLow"));
        sizePolicy.setHeightForWidth(cannyLow->sizePolicy().hasHeightForWidth());
        cannyLow->setSizePolicy(sizePolicy);
        cannyLow->setMaximumSize(QSize(16777215, 16777215));
        cannyLow->setButtonSymbols(QAbstractSpinBox::NoButtons);
        cannyLow->setMinimum(0);
        cannyLow->setMaximum(255);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, cannyLow);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_6);

        cannyHigh = new QSpinBox(groupBox_3);
        cannyHigh->setObjectName(QString::fromUtf8("cannyHigh"));
        sizePolicy.setHeightForWidth(cannyHigh->sizePolicy().hasHeightForWidth());
        cannyHigh->setSizePolicy(sizePolicy);
        cannyHigh->setMaximumSize(QSize(16777215, 16777215));
        cannyHigh->setButtonSymbols(QAbstractSpinBox::NoButtons);
        cannyHigh->setMinimum(0);
        cannyHigh->setMaximum(255);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, cannyHigh);


        horizontalLayout_3->addLayout(formLayout_2);


        verticalLayout_3->addWidget(groupBox_3);


        horizontalLayout_8->addWidget(widget);


        retranslateUi(CannySettings);
        QObject::connect(centerMin, SIGNAL(valueChanged(int)), CannySettings, SLOT(setVOICenterMinimum(int)));
        QObject::connect(centerMax, SIGNAL(valueChanged(int)), CannySettings, SLOT(setVOICenterMaximum(int)));
        QObject::connect(widthMin, SIGNAL(valueChanged(int)), CannySettings, SLOT(setVOIWidthMinimum(int)));
        QObject::connect(widthMax, SIGNAL(valueChanged(int)), CannySettings, SLOT(setVOIWidthMaximum(int)));
        QObject::connect(centerSlider, SIGNAL(valueChanged(int)), centerVal, SLOT(setValue(int)));
        QObject::connect(centerVal, SIGNAL(valueChanged(int)), centerSlider, SLOT(setValue(int)));
        QObject::connect(widthVal, SIGNAL(valueChanged(int)), widthSlider, SLOT(setValue(int)));
        QObject::connect(widthSlider, SIGNAL(valueChanged(int)), widthVal, SLOT(setValue(int)));
        QObject::connect(centerVal, SIGNAL(valueChanged(int)), CannySettings, SLOT(emitSettingsChanged()));
        QObject::connect(widthVal, SIGNAL(valueChanged(int)), CannySettings, SLOT(emitSettingsChanged()));
        QObject::connect(gaussKernel, SIGNAL(valueChanged(int)), CannySettings, SLOT(emitSettingsChanged()));
        QObject::connect(gaussSigma, SIGNAL(valueChanged(double)), CannySettings, SLOT(emitSettingsChanged()));
        QObject::connect(cannyLow, SIGNAL(valueChanged(int)), CannySettings, SLOT(emitSettingsChanged()));
        QObject::connect(cannyHigh, SIGNAL(valueChanged(int)), CannySettings, SLOT(emitSettingsChanged()));
        QObject::connect(radioVoi, SIGNAL(clicked()), CannySettings, SLOT(emitSettingsChanged()));
        QObject::connect(radioGauss, SIGNAL(clicked()), CannySettings, SLOT(emitSettingsChanged()));
        QObject::connect(radioCanny, SIGNAL(clicked()), CannySettings, SLOT(emitSettingsChanged()));

        QMetaObject::connectSlotsByName(CannySettings);
    } // setupUi

    void retranslateUi(QWidget *CannySettings)
    {
        CannySettings->setWindowTitle(QApplication::translate("CannySettings", "CannySettings", nullptr));
        groupBox_4->setTitle(QApplication::translate("CannySettings", "\320\250\320\260\320\263\320\270 \320\262\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217", nullptr));
        radioVoi->setText(QApplication::translate("CannySettings", "VOI \320\277\321\200\320\265\320\276\320\261\321\200\320\260\320\267\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        radioGauss->setText(QApplication::translate("CannySettings", "\320\240\320\260\320\267\320\274\321\213\321\202\320\270\320\265 \320\223\320\260\321\203\321\201\321\201\320\260", nullptr));
        radioCanny->setText(QApplication::translate("CannySettings", "\320\244\320\270\320\273\321\214\321\202\321\200 Canny", nullptr));
        defaultButton->setText(QApplication::translate("CannySettings", "\320\237\320\276 \321\203\320\274\320\276\320\273\321\207\320\260\320\275\320\270\321\216", nullptr));
        groupBox->setTitle(QApplication::translate("CannySettings", "1. VOI \320\277\321\200\320\265\320\276\320\261\321\200\320\260\320\267\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        label->setText(QApplication::translate("CannySettings", "Window Center", nullptr));
        label_7->setText(QApplication::translate("CannySettings", "\320\234\320\270\320\275\320\270\320\274\321\203\320\274", nullptr));
        label_8->setText(QApplication::translate("CannySettings", "\320\234\320\260\320\272\321\201\320\270\320\274\321\203\320\274", nullptr));
        label_2->setText(QApplication::translate("CannySettings", "Window Width", nullptr));
        label_9->setText(QApplication::translate("CannySettings", "\320\234\320\270\320\275\320\270\320\274\321\203\320\274", nullptr));
        label_10->setText(QApplication::translate("CannySettings", "\320\234\320\260\320\272\321\201\320\270\320\274\321\203\320\274", nullptr));
        groupBox_2->setTitle(QApplication::translate("CannySettings", "2. \320\240\320\260\320\267\320\274\321\213\321\202\320\270\320\265 \320\223\320\260\321\203\321\201\321\201\320\260", nullptr));
        label_3->setText(QApplication::translate("CannySettings", "\320\257\320\264\321\200\320\276 \321\201\320\262\321\221\321\200\321\202\320\272\320\270", nullptr));
        label_4->setText(QApplication::translate("CannySettings", "\320\241\320\270\320\263\320\274\320\260", nullptr));
        groupBox_3->setTitle(QApplication::translate("CannySettings", "3. \320\237\320\276\321\200\320\276\320\263 Canny", nullptr));
        label_5->setText(QApplication::translate("CannySettings", "\320\235\320\270\320\266\320\275\320\270\320\271 \320\277\320\276\321\200\320\276\320\263", nullptr));
        label_6->setText(QApplication::translate("CannySettings", "\320\222\320\265\321\200\321\205\320\275\320\270\320\271 \320\277\320\276\321\200\320\276\320\263", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CannySettings: public Ui_CannySettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANNYSETTINGS_H

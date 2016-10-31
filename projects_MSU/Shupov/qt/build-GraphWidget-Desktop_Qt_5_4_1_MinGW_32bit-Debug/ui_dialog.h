/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include "dialog.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *VertexLabel;
    QSpinBox *VertexNumberBox;
    QLabel *EdgesLabel;
    QSpinBox *EdgesNumberbox;
    QLabel *ComponentLabel;
    QSpinBox *ComponentNumberBox;
    QSpinBox *MaxDegreeNumberBox;
    QLabel *MaxDegreeLabel;
    QLabel *MinDegreeLabel;
    QSpinBox *MinDegreeNumberBox;

    void setupUi(Dialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(373, 202);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(290, 10, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        VertexLabel = new QLabel(Dialog);
        VertexLabel->setObjectName(QStringLiteral("VertexLabel"));
        VertexLabel->setGeometry(QRect(10, 10, 141, 21));
        VertexNumberBox = new QSpinBox(Dialog);
        VertexNumberBox->setObjectName(QStringLiteral("VertexNumberBox"));
        VertexNumberBox->setGeometry(QRect(211, 10, 71, 22));
        VertexNumberBox->setMinimum(1);
        VertexNumberBox->setValue(5);
        EdgesLabel = new QLabel(Dialog);
        EdgesLabel->setObjectName(QStringLiteral("EdgesLabel"));
        EdgesLabel->setGeometry(QRect(10, 50, 131, 21));
        EdgesNumberbox = new QSpinBox(Dialog);
        EdgesNumberbox->setObjectName(QStringLiteral("EdgesNumberbox"));
        EdgesNumberbox->setGeometry(QRect(211, 50, 71, 22));
        EdgesNumberbox->setMaximum(9999);
        EdgesNumberbox->setValue(10);
        ComponentLabel = new QLabel(Dialog);
        ComponentLabel->setObjectName(QStringLiteral("ComponentLabel"));
        ComponentLabel->setGeometry(QRect(10, 90, 181, 21));
        ComponentNumberBox = new QSpinBox(Dialog);
        ComponentNumberBox->setObjectName(QStringLiteral("ComponentNumberBox"));
        ComponentNumberBox->setGeometry(QRect(211, 90, 71, 22));
        ComponentNumberBox->setMinimum(1);
        MaxDegreeNumberBox = new QSpinBox(Dialog);
        MaxDegreeNumberBox->setObjectName(QStringLiteral("MaxDegreeNumberBox"));
        MaxDegreeNumberBox->setGeometry(QRect(211, 130, 71, 22));
        MaxDegreeNumberBox->setValue(4);
        MaxDegreeLabel = new QLabel(Dialog);
        MaxDegreeLabel->setObjectName(QStringLiteral("MaxDegreeLabel"));
        MaxDegreeLabel->setGeometry(QRect(10, 130, 181, 21));
        MinDegreeLabel = new QLabel(Dialog);
        MinDegreeLabel->setObjectName(QStringLiteral("MinDegreeLabel"));
        MinDegreeLabel->setGeometry(QRect(10, 170, 181, 16));
        MinDegreeNumberBox = new QSpinBox(Dialog);
        MinDegreeNumberBox->setObjectName(QStringLiteral("MinDegreeNumberBox"));
        MinDegreeNumberBox->setGeometry(QRect(211, 170, 71, 22));
        MinDegreeNumberBox->setValue(4);

        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(Dialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        VertexLabel->setText(QApplication::translate("Dialog", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\262\320\265\321\200\321\210\320\270\320\275 \320\263\321\200\320\260\321\204\320\260", 0));
        EdgesLabel->setText(QApplication::translate("Dialog", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\200\321\221\320\261\320\265\321\200 \320\263\321\200\320\260\321\204\320\260", 0));
        ComponentLabel->setText(QApplication::translate("Dialog", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\272\320\276\320\274\320\277\320\276\320\275\320\265\320\275\321\202 \321\201\320\262\321\217\320\267\320\275\320\276\321\201\321\202\320\270", 0));
        MaxDegreeLabel->setText(QApplication::translate("Dialog", "\320\234\320\260\320\272\321\201\320\270\320\274\320\260\320\273\321\214\320\275\320\260\321\217 \321\201\321\202\320\265\320\277\320\265\320\275\321\214 \320\262\320\265\321\200\321\210\320\270\320\275\321\213", 0));
        MinDegreeLabel->setText(QApplication::translate("Dialog", "\320\234\320\270\320\275\320\270\320\274\320\260\320\273\321\214\320\275\320\260\321\217 \321\201\321\202\320\265\320\277\320\265\320\275\321\214 \320\262\320\265\321\200\321\210\320\270\320\275\321\213", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H

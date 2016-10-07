/********************************************************************************
** Form generated from reading UI file 'beijingsubway_co.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEIJINGSUBWAY_CO_H
#define UI_BEIJINGSUBWAY_CO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BeijingSubway_coClass
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BeijingSubway_coClass)
    {
        if (BeijingSubway_coClass->objectName().isEmpty())
            BeijingSubway_coClass->setObjectName(QStringLiteral("BeijingSubway_coClass"));
        BeijingSubway_coClass->resize(1070, 750);
        centralWidget = new QWidget(BeijingSubway_coClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 900, 600));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 670, 141, 41));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(180, 670, 141, 41));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(360, 670, 141, 41));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(560, 670, 141, 41));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(730, 670, 141, 41));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 630, 61, 31));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(230, 630, 61, 31));
        label_2->setFont(font);
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(390, 630, 81, 31));
        label_3->setFont(font);
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(910, 1, 151, 591));
        BeijingSubway_coClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(BeijingSubway_coClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BeijingSubway_coClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BeijingSubway_coClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BeijingSubway_coClass->setStatusBar(statusBar);

        retranslateUi(BeijingSubway_coClass);

        QMetaObject::connectSlotsByName(BeijingSubway_coClass);
    } // setupUi

    void retranslateUi(QMainWindow *BeijingSubway_coClass)
    {
        BeijingSubway_coClass->setWindowTitle(QApplication::translate("BeijingSubway_coClass", "\345\214\227\344\272\254\345\234\260\351\223\201\346\237\245\350\257\242\347\263\273\347\273\237", 0));
        pushButton->setText(QApplication::translate("BeijingSubway_coClass", "\346\237\245\350\257\242", 0));
        pushButton_2->setText(QApplication::translate("BeijingSubway_coClass", "\351\207\215\347\275\256", 0));
        label->setText(QApplication::translate("BeijingSubway_coClass", "\350\265\267\347\202\271", 0));
        label_2->setText(QApplication::translate("BeijingSubway_coClass", "\347\273\210\347\202\271", 0));
        label_3->setText(QApplication::translate("BeijingSubway_coClass", "\346\234\200\347\237\255\346\250\241\345\274\217", 0));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BeijingSubway_coClass: public Ui_BeijingSubway_coClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEIJINGSUBWAY_CO_H

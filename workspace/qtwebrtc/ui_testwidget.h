/********************************************************************************
** Form generated from reading UI file 'testwidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTWIDGET_H
#define UI_TESTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestWidget
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_pStartButton;
    QPushButton *m_pProcessAnswerButton;
    QPushButton *m_pProcessRemoteICEButton;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_3;
    QPlainTextEdit *m_pOfferText;
    QPlainTextEdit *m_pAnswerText;
    QLabel *label_4;
    QLabel *label_5;
    QPlainTextEdit *m_pOwnICEText;
    QPlainTextEdit *m_pRemoteICEText;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TestWidget)
    {
        if (TestWidget->objectName().isEmpty())
            TestWidget->setObjectName(QString::fromUtf8("TestWidget"));
        TestWidget->resize(872, 600);
        centralwidget = new QWidget(TestWidget);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(26);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_pStartButton = new QPushButton(centralwidget);
        m_pStartButton->setObjectName(QString::fromUtf8("m_pStartButton"));

        horizontalLayout->addWidget(m_pStartButton);

        m_pProcessAnswerButton = new QPushButton(centralwidget);
        m_pProcessAnswerButton->setObjectName(QString::fromUtf8("m_pProcessAnswerButton"));

        horizontalLayout->addWidget(m_pProcessAnswerButton);

        m_pProcessRemoteICEButton = new QPushButton(centralwidget);
        m_pProcessRemoteICEButton->setObjectName(QString::fromUtf8("m_pProcessRemoteICEButton"));

        horizontalLayout->addWidget(m_pProcessRemoteICEButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        m_pOfferText = new QPlainTextEdit(centralwidget);
        m_pOfferText->setObjectName(QString::fromUtf8("m_pOfferText"));

        gridLayout->addWidget(m_pOfferText, 1, 0, 1, 1);

        m_pAnswerText = new QPlainTextEdit(centralwidget);
        m_pAnswerText->setObjectName(QString::fromUtf8("m_pAnswerText"));

        gridLayout->addWidget(m_pAnswerText, 1, 1, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 1, 1, 1);

        m_pOwnICEText = new QPlainTextEdit(centralwidget);
        m_pOwnICEText->setObjectName(QString::fromUtf8("m_pOwnICEText"));

        gridLayout->addWidget(m_pOwnICEText, 3, 0, 1, 1);

        m_pRemoteICEText = new QPlainTextEdit(centralwidget);
        m_pRemoteICEText->setObjectName(QString::fromUtf8("m_pRemoteICEText"));

        gridLayout->addWidget(m_pRemoteICEText, 3, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 0, 1, 1);

        TestWidget->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TestWidget);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 872, 21));
        TestWidget->setMenuBar(menubar);
        statusbar = new QStatusBar(TestWidget);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        TestWidget->setStatusBar(statusbar);

        retranslateUi(TestWidget);

        QMetaObject::connectSlotsByName(TestWidget);
    } // setupUi

    void retranslateUi(QMainWindow *TestWidget)
    {
        TestWidget->setWindowTitle(QApplication::translate("TestWidget", "TestWidget", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TestWidget", "Sender", 0, QApplication::UnicodeUTF8));
        m_pStartButton->setText(QApplication::translate("TestWidget", "Start", 0, QApplication::UnicodeUTF8));
        m_pProcessAnswerButton->setText(QApplication::translate("TestWidget", "Process answer", 0, QApplication::UnicodeUTF8));
        m_pProcessRemoteICEButton->setText(QApplication::translate("TestWidget", "Process remote ICE info", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TestWidget", "This is the SDP data that will need to be sent to the other side", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("TestWidget", "Paste the SDP info from the other side here and press 'process answer'", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("TestWidget", "This is ICE info for the local host, we'll need to send it to the remote end", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("TestWidget", "Paste the ICE info from the remote host here and press 'process ICE candidates'", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TestWidget: public Ui_TestWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWIDGET_H

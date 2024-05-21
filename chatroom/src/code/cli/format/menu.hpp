/********************************************************************************
** Form generated from reading UI file 'menuWiaDBu.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MENUWIADBU_H
#define MENUWIADBU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_welcome
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *Login;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *id_log;
    QLabel *label_2;
    QLineEdit *passwd_log;
    QPushButton *login;
    QPushButton *quit1;
    QWidget *Register;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLineEdit *name_reg;
    QLabel *label_5;
    QLineEdit *passwd_reg;
    QLabel *label_7;
    QComboBox *questions;
    QLabel *label_6;
    QLineEdit *ans;
    QPushButton *Reg;
    QPushButton *quit2;

    void setupUi(QDialog *welcome)
    {
        if (welcome->objectName().isEmpty())
            welcome->setObjectName(QString::fromUtf8("welcome"));
        welcome->resize(261, 249);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(welcome->sizePolicy().hasHeightForWidth());
        welcome->setSizePolicy(sizePolicy);
        welcome->setMaximumSize(QSize(261, 249));
        welcome->setLayoutDirection(Qt::LeftToRight);
        welcome->setInputMethodHints(Qt::ImhPreferNumbers);
        welcome->setSizeGripEnabled(true);
        welcome->setModal(true);
        gridLayout = new QGridLayout(welcome);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(welcome);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(56);
        sizePolicy1.setVerticalStretch(56);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMaximumSize(QSize(243, 231));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setAutoFillBackground(true);
        tabWidget->setInputMethodHints(Qt::ImhNone);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(128, 16));
        tabWidget->setElideMode(Qt::ElideMiddle);
        tabWidget->setTabBarAutoHide(false);
        Login = new QWidget();
        Login->setObjectName(QString::fromUtf8("Login"));
        Login->setAutoFillBackground(true);
        gridLayout_3 = new QGridLayout(Login);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_3 = new QLabel(Login);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(16777215, 64));
        label_3->setTextFormat(Qt::AutoText);
        label_3->setScaledContents(false);
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setWordWrap(false);
        label_3->setTextInteractionFlags(Qt::LinksAccessibleByMouse);

        gridLayout_3->addWidget(label_3, 0, 0, 1, 2);

        label = new QLabel(Login);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label, 1, 0, 1, 1);

        id_log = new QLineEdit(Login);
        id_log->setObjectName(QString::fromUtf8("id_log"));
        id_log->setTabletTracking(false);
        id_log->setFocusPolicy(Qt::StrongFocus);
        id_log->setContextMenuPolicy(Qt::DefaultContextMenu);
        id_log->setLayoutDirection(Qt::LeftToRight);
        id_log->setInputMethodHints(Qt::ImhNone);
        id_log->setMaxLength(10);
        id_log->setEchoMode(QLineEdit::Normal);
        id_log->setClearButtonEnabled(true);

        gridLayout_3->addWidget(id_log, 1, 1, 1, 1);

        label_2 = new QLabel(Login);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_2, 2, 0, 1, 1);

        passwd_log = new QLineEdit(Login);
        passwd_log->setObjectName(QString::fromUtf8("passwd_log"));
        passwd_log->setTabletTracking(false);
        passwd_log->setFocusPolicy(Qt::StrongFocus);
        passwd_log->setContextMenuPolicy(Qt::DefaultContextMenu);
        passwd_log->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        passwd_log->setMaxLength(16);
        passwd_log->setEchoMode(QLineEdit::Password);
        passwd_log->setClearButtonEnabled(true);

        gridLayout_3->addWidget(passwd_log, 2, 1, 1, 1);

        login = new QPushButton(Login);
        login->setObjectName(QString::fromUtf8("login"));

        gridLayout_3->addWidget(login, 3, 1, 1, 1);

        quit1 = new QPushButton(Login);
        quit1->setObjectName(QString::fromUtf8("quit1"));

        gridLayout_3->addWidget(quit1, 4, 1, 1, 1);

        tabWidget->addTab(Login, QString());
        Register = new QWidget();
        Register->setObjectName(QString::fromUtf8("Register"));
        Register->setLayoutDirection(Qt::LeftToRight);
        Register->setAutoFillBackground(true);
        gridLayout_2 = new QGridLayout(Register);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_4 = new QLabel(Register);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        name_reg = new QLineEdit(Register);
        name_reg->setObjectName(QString::fromUtf8("name_reg"));
        name_reg->setMaxLength(128);
        name_reg->setClearButtonEnabled(true);

        gridLayout_2->addWidget(name_reg, 0, 1, 1, 1);

        label_5 = new QLabel(Register);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        passwd_reg = new QLineEdit(Register);
        passwd_reg->setObjectName(QString::fromUtf8("passwd_reg"));
        passwd_reg->setMaxLength(16);
        passwd_reg->setFrame(true);
        passwd_reg->setEchoMode(QLineEdit::Password);
        passwd_reg->setDragEnabled(false);
        passwd_reg->setClearButtonEnabled(true);

        gridLayout_2->addWidget(passwd_reg, 1, 1, 1, 1);

        label_7 = new QLabel(Register);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 2, 0, 1, 1);

        questions = new QComboBox(Register);
        questions->addItem(QString());
        questions->addItem(QString());
        questions->addItem(QString());
        questions->addItem(QString());
        questions->addItem(QString());
        questions->setObjectName(QString::fromUtf8("questions"));

        gridLayout_2->addWidget(questions, 2, 1, 1, 1);

        label_6 = new QLabel(Register);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 3, 0, 1, 1);

        ans = new QLineEdit(Register);
        ans->setObjectName(QString::fromUtf8("ans"));
        ans->setClearButtonEnabled(true);

        gridLayout_2->addWidget(ans, 3, 1, 1, 1);

        Reg = new QPushButton(Register);
        Reg->setObjectName(QString::fromUtf8("Reg"));

        gridLayout_2->addWidget(Reg, 4, 1, 1, 1);

        quit2 = new QPushButton(Register);
        quit2->setObjectName(QString::fromUtf8("quit2"));

        gridLayout_2->addWidget(quit2, 5, 1, 1, 1);

        tabWidget->addTab(Register, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        QWidget::setTabOrder(id_log, passwd_log);
        QWidget::setTabOrder(passwd_log, login);
        QWidget::setTabOrder(login, quit1);
        QWidget::setTabOrder(quit1, name_reg);
        QWidget::setTabOrder(name_reg, passwd_reg);
        QWidget::setTabOrder(passwd_reg, questions);
        QWidget::setTabOrder(questions, ans);
        QWidget::setTabOrder(ans, Reg);
        QWidget::setTabOrder(Reg, quit2);

        retranslateUi(welcome);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(welcome);
    } // setupUi

    void retranslateUi(QDialog *welcome)
    {
        welcome->setWindowTitle(QCoreApplication::translate("welcome", "Ph0m's Chatroom", nullptr));
#if QT_CONFIG(tooltip)
        tabWidget->setToolTip(QCoreApplication::translate("welcome", "<html><head/><body><p>Login</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_3->setText(QCoreApplication::translate("welcome", "<html><head/><body><p><span style=\" font-size:24pt; font-weight:600; font-style:italic; color:#0e8ddc;\">Welcome</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("welcome", "\345\270\220\345\217\267\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("welcome", "\345\257\206\347\240\201\357\274\232", nullptr));
        login->setText(QCoreApplication::translate("welcome", "\347\231\273\345\275\225", nullptr));
        quit1->setText(QCoreApplication::translate("welcome", "\351\200\200\345\207\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Login), QCoreApplication::translate("welcome", "Login", nullptr));
        label_4->setText(QCoreApplication::translate("welcome", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_5->setText(QCoreApplication::translate("welcome", "\345\257\206   \347\240\201", nullptr));
        label_7->setText(QCoreApplication::translate("welcome", "\345\257\206   \344\277\235", nullptr));
        questions->setItemText(0, QCoreApplication::translate("welcome", "\346\227\240<\345\277\230\350\256\260\345\257\206\347\240\201\345\220\216\346\227\240\346\263\225\346\211\276\345\233\236>", nullptr));
        questions->setItemText(1, QCoreApplication::translate("welcome", "\344\275\240\347\232\204\347\224\237\346\227\245\357\274\237", nullptr));
        questions->setItemText(2, QCoreApplication::translate("welcome", "\344\275\240\346\257\215\344\272\262\347\232\204\345\220\215\345\255\227\357\274\237", nullptr));
        questions->setItemText(3, QCoreApplication::translate("welcome", "\344\275\240\347\210\266\344\272\262\347\232\204\345\220\215\345\255\227\357\274\237", nullptr));
        questions->setItemText(4, QCoreApplication::translate("welcome", "\344\275\240\345\255\246\346\240\241\347\232\204\345\220\215\345\255\227\357\274\237", nullptr));

        label_6->setText(QCoreApplication::translate("welcome", "\347\255\224   \346\241\210", nullptr));
        Reg->setText(QCoreApplication::translate("welcome", "\346\263\250\345\206\214", nullptr));
        quit2->setText(QCoreApplication::translate("welcome", "\351\200\200\345\207\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Register), QCoreApplication::translate("welcome", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class welcome: public Ui_welcome {

    };
} // namespace Ui

QT_END_NAMESPACE

#endif // MENUWIADBU_H

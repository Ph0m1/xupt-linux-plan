/********************************************************************************
** Form generated from reading UI file 'designerxvcShy.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DESIGNERXVCSHY_H
#define DESIGNERXVCSHY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatroom
{
public:
    QTabWidget *tabWidget;
    QWidget *Login;
    QLabel *label_3;
    QLineEdit *id;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *passwd;
    QPushButton *login;
    QPushButton *pushButton;
    QWidget *Register;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *chatroom)
    {
        if (chatroom->objectName().isEmpty())
            chatroom->setObjectName(QString::fromUtf8("chatroom"));
        chatroom->resize(400, 300);
        chatroom->setInputMethodHints(Qt::ImhPreferNumbers);
        chatroom->setSizeGripEnabled(true);
        chatroom->setModal(true);
        tabWidget = new QTabWidget(chatroom);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 401, 301));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(56);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(128, 16));
        tabWidget->setTabBarAutoHide(false);
        Login = new QWidget();
        Login->setObjectName(QString::fromUtf8("Login"));
        label_3 = new QLabel(Login);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(130, 0, 131, 61));
        label_3->setTextFormat(Qt::AutoText);
        label_3->setScaledContents(false);
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setWordWrap(false);
        label_3->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        id = new QLineEdit(Login);
        id->setObjectName(QString::fromUtf8("id"));
        id->setGeometry(QRect(140, 60, 113, 25));
        id->setTabletTracking(false);
        id->setFocusPolicy(Qt::StrongFocus);
        id->setContextMenuPolicy(Qt::DefaultContextMenu);
        id->setInputMethodHints(Qt::ImhNone);
        id->setEchoMode(QLineEdit::Normal);
        id->setClearButtonEnabled(true);
        label = new QLabel(Login);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 60, 60, 17));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(Login);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 110, 60, 17));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        passwd = new QLineEdit(Login);
        passwd->setObjectName(QString::fromUtf8("passwd"));
        passwd->setGeometry(QRect(140, 110, 113, 25));
        passwd->setTabletTracking(false);
        passwd->setFocusPolicy(Qt::StrongFocus);
        passwd->setContextMenuPolicy(Qt::DefaultContextMenu);
        passwd->setInputMethodHints(Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        passwd->setEchoMode(QLineEdit::Password);
        passwd->setClearButtonEnabled(true);
        login = new QPushButton(Login);
        login->setObjectName(QString::fromUtf8("login"));
        login->setGeometry(QRect(150, 170, 80, 25));
        pushButton = new QPushButton(Login);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 200, 80, 25));
        tabWidget->addTab(Login, QString());
        Register = new QWidget();
        Register->setObjectName(QString::fromUtf8("Register"));
        lineEdit = new QLineEdit(Register);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(120, 40, 113, 25));
        lineEdit_2 = new QLineEdit(Register);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(120, 80, 113, 25));
        lineEdit_3 = new QLineEdit(Register);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(120, 120, 113, 25));
        lineEdit_4 = new QLineEdit(Register);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(120, 160, 113, 25));
        pushButton_2 = new QPushButton(Register);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(140, 200, 80, 25));
        pushButton_3 = new QPushButton(Register);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(140, 230, 80, 25));
        tabWidget->addTab(Register, QString());

        retranslateUi(chatroom);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(chatroom);
    } // setupUi

    void retranslateUi(QDialog *chatroom)
    {
        chatroom->setWindowTitle(QCoreApplication::translate("chatroom", "Dialog", nullptr));
#if QT_CONFIG(tooltip)
        tabWidget->setToolTip(QCoreApplication::translate("chatroom", "<html><head/><body><p>Login</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_3->setText(QCoreApplication::translate("chatroom", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600; font-style:italic; color:#0e8ddc;\">Wlecome</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("chatroom", "\345\270\220\345\217\267\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("chatroom", "\345\257\206\347\240\201\357\274\232", nullptr));
        login->setText(QCoreApplication::translate("chatroom", "\347\231\273\345\275\225", nullptr));
        pushButton->setText(QCoreApplication::translate("chatroom", "\351\200\200\345\207\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Login), QCoreApplication::translate("chatroom", "Login", nullptr));
        pushButton_2->setText(QCoreApplication::translate("chatroom", "\346\263\250\345\206\214", nullptr));
        pushButton_3->setText(QCoreApplication::translate("chatroom", "\351\200\200\345\207\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Register), QCoreApplication::translate("chatroom", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chatroom: public Ui_chatroom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DESIGNERXVCSHY_H

/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qchartview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindowDesign
{
public:
    QAction *action_Quit;
    QAction *action_Preferences;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QWidget *centralwidget;
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_com;
    QGridLayout *gridLayout_4;
    QListView *listView_com;
    QGroupBox *groupBox_eve;
    QGridLayout *gridLayout_5;
    QListView *listView_eve;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_port;
    QPushButton *button_connect;
    QLineEdit *lineEdit_ip;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_6;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox_notch;
    QCheckBox *checkBox_high;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_high;
    QCheckBox *checkBox_low;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox_low;
    QWidget *tab_2;
    QGridLayout *gridLayout_8;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBox_notch_2;
    QCheckBox *checkBox_high_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox_high_2;
    QCheckBox *checkBox_low_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_low_2;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox_config;
    QGridLayout *gridLayout_3;
    QListView *listView_config;
    QGridLayout *gridLayout_chartwidget;
    QChartView *chartwidget;
    QMenuBar *menubar;
    QMenu *menu_File;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindowDesign)
    {
        if (MainWindowDesign->objectName().isEmpty())
            MainWindowDesign->setObjectName(QStringLiteral("MainWindowDesign"));
        MainWindowDesign->resize(1076, 615);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowDesign->setWindowIcon(icon);
        MainWindowDesign->setLocale(QLocale(QLocale::English, QLocale::Australia));
        action_Quit = new QAction(MainWindowDesign);
        action_Quit->setObjectName(QStringLiteral("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        action_Preferences = new QAction(MainWindowDesign);
        action_Preferences->setObjectName(QStringLiteral("action_Preferences"));
        actionAbout = new QAction(MainWindowDesign);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAbout_Qt = new QAction(MainWindowDesign);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        centralwidget = new QWidget(MainWindowDesign);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_7 = new QGridLayout(centralwidget);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_com = new QGroupBox(centralwidget);
        groupBox_com->setObjectName(QStringLiteral("groupBox_com"));
        gridLayout_4 = new QGridLayout(groupBox_com);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        listView_com = new QListView(groupBox_com);
        listView_com->setObjectName(QStringLiteral("listView_com"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listView_com->sizePolicy().hasHeightForWidth());
        listView_com->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(listView_com, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_com, 2, 0, 1, 1);

        groupBox_eve = new QGroupBox(centralwidget);
        groupBox_eve->setObjectName(QStringLiteral("groupBox_eve"));
        gridLayout_5 = new QGridLayout(groupBox_eve);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        listView_eve = new QListView(groupBox_eve);
        listView_eve->setObjectName(QStringLiteral("listView_eve"));
        sizePolicy.setHeightForWidth(listView_eve->sizePolicy().hasHeightForWidth());
        listView_eve->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(listView_eve, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_eve, 3, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_port = new QLineEdit(centralwidget);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));
        sizePolicy.setHeightForWidth(lineEdit_port->sizePolicy().hasHeightForWidth());
        lineEdit_port->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(lineEdit_port, 1, 1, 1, 1);

        button_connect = new QPushButton(centralwidget);
        button_connect->setObjectName(QStringLiteral("button_connect"));
        sizePolicy.setHeightForWidth(button_connect->sizePolicy().hasHeightForWidth());
        button_connect->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(button_connect, 2, 0, 1, 2);

        lineEdit_ip = new QLineEdit(centralwidget);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));
        sizePolicy.setHeightForWidth(lineEdit_ip->sizePolicy().hasHeightForWidth());
        lineEdit_ip->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(lineEdit_ip, 0, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 2);

        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_6 = new QGridLayout(tab);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(9, 9, 9, 9);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        checkBox_notch = new QCheckBox(tab);
        checkBox_notch->setObjectName(QStringLiteral("checkBox_notch"));
        checkBox_notch->setChecked(false);

        verticalLayout->addWidget(checkBox_notch);

        checkBox_high = new QCheckBox(tab);
        checkBox_high->setObjectName(QStringLiteral("checkBox_high"));

        verticalLayout->addWidget(checkBox_high);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        doubleSpinBox_high = new QDoubleSpinBox(tab);
        doubleSpinBox_high->setObjectName(QStringLiteral("doubleSpinBox_high"));
        doubleSpinBox_high->setMaximum(1000);

        horizontalLayout->addWidget(doubleSpinBox_high);


        verticalLayout->addLayout(horizontalLayout);

        checkBox_low = new QCheckBox(tab);
        checkBox_low->setObjectName(QStringLiteral("checkBox_low"));

        verticalLayout->addWidget(checkBox_low);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        doubleSpinBox_low = new QDoubleSpinBox(tab);
        doubleSpinBox_low->setObjectName(QStringLiteral("doubleSpinBox_low"));
        doubleSpinBox_low->setMaximum(1000);

        horizontalLayout_2->addWidget(doubleSpinBox_low);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout_6->addLayout(verticalLayout, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_8 = new QGridLayout(tab_2);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        checkBox_notch_2 = new QCheckBox(tab_2);
        checkBox_notch_2->setObjectName(QStringLiteral("checkBox_notch_2"));
        checkBox_notch_2->setChecked(false);

        verticalLayout_3->addWidget(checkBox_notch_2);

        checkBox_high_2 = new QCheckBox(tab_2);
        checkBox_high_2->setObjectName(QStringLiteral("checkBox_high_2"));

        verticalLayout_3->addWidget(checkBox_high_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        doubleSpinBox_high_2 = new QDoubleSpinBox(tab_2);
        doubleSpinBox_high_2->setObjectName(QStringLiteral("doubleSpinBox_high_2"));
        doubleSpinBox_high_2->setMaximum(1000);

        horizontalLayout_3->addWidget(doubleSpinBox_high_2);


        verticalLayout_3->addLayout(horizontalLayout_3);

        checkBox_low_2 = new QCheckBox(tab_2);
        checkBox_low_2->setObjectName(QStringLiteral("checkBox_low_2"));

        verticalLayout_3->addWidget(checkBox_low_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_4->addWidget(label_6);

        doubleSpinBox_low_2 = new QDoubleSpinBox(tab_2);
        doubleSpinBox_low_2->setObjectName(QStringLiteral("doubleSpinBox_low_2"));
        doubleSpinBox_low_2->setMaximum(1000);

        horizontalLayout_4->addWidget(doubleSpinBox_low_2);


        verticalLayout_3->addLayout(horizontalLayout_4);


        gridLayout_8->addLayout(verticalLayout_3, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer_2, 1, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 4, 1);

        groupBox_config = new QGroupBox(centralwidget);
        groupBox_config->setObjectName(QStringLiteral("groupBox_config"));
        sizePolicy.setHeightForWidth(groupBox_config->sizePolicy().hasHeightForWidth());
        groupBox_config->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(groupBox_config);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(6);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        listView_config = new QListView(groupBox_config);
        listView_config->setObjectName(QStringLiteral("listView_config"));
        sizePolicy.setHeightForWidth(listView_config->sizePolicy().hasHeightForWidth());
        listView_config->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(listView_config, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_config, 1, 0, 1, 1);

        gridLayout_chartwidget = new QGridLayout();
        gridLayout_chartwidget->setSpacing(0);
        gridLayout_chartwidget->setObjectName(QStringLiteral("gridLayout_chartwidget"));
        chartwidget = new QChartView(centralwidget);
        chartwidget->setObjectName(QStringLiteral("chartwidget"));
        sizePolicy.setHeightForWidth(chartwidget->sizePolicy().hasHeightForWidth());
        chartwidget->setSizePolicy(sizePolicy);

        gridLayout_chartwidget->addWidget(chartwidget, 0, 0, 1, 1);

        gridLayout_chartwidget->setRowStretch(0, 1);

        gridLayout->addLayout(gridLayout_chartwidget, 0, 2, 4, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 2);
        gridLayout->setRowStretch(2, 3);
        gridLayout->setRowStretch(3, 3);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(2, 8);

        gridLayout_7->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindowDesign->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowDesign);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1076, 28));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        MainWindowDesign->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowDesign);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindowDesign->setStatusBar(statusbar);

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(action_Preferences);
        menu_File->addSeparator();
        menu_File->addAction(actionAbout);
        menu_File->addAction(actionAbout_Qt);
        menu_File->addSeparator();
        menu_File->addAction(action_Quit);

        retranslateUi(MainWindowDesign);
        QObject::connect(action_Quit, SIGNAL(triggered()), MainWindowDesign, SLOT(close()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindowDesign);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowDesign)
    {
        MainWindowDesign->setWindowTitle(QApplication::translate("MainWindowDesign", "QRosApp", Q_NULLPTR));
        action_Quit->setText(QApplication::translate("MainWindowDesign", "&Quit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_Quit->setShortcut(QApplication::translate("MainWindowDesign", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_Preferences->setText(QApplication::translate("MainWindowDesign", "&Preferences", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindowDesign", "&About", Q_NULLPTR));
        actionAbout_Qt->setText(QApplication::translate("MainWindowDesign", "About &Qt", Q_NULLPTR));
        groupBox_com->setTitle(QApplication::translate("MainWindowDesign", "Communication Log", Q_NULLPTR));
        groupBox_eve->setTitle(QApplication::translate("MainWindowDesign", "Events Log", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindowDesign", "IP", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindowDesign", "Port", Q_NULLPTR));
        lineEdit_port->setText(QApplication::translate("MainWindowDesign", "4455", Q_NULLPTR));
        button_connect->setText(QApplication::translate("MainWindowDesign", "Connect", Q_NULLPTR));
        lineEdit_ip->setText(QApplication::translate("MainWindowDesign", "192.170.0.2", Q_NULLPTR));
        checkBox_notch->setText(QApplication::translate("MainWindowDesign", "50 Hz", Q_NULLPTR));
        checkBox_high->setText(QApplication::translate("MainWindowDesign", "High Pass", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindowDesign", "Freq.[Hz]", Q_NULLPTR));
        checkBox_low->setText(QApplication::translate("MainWindowDesign", "Low Pass", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindowDesign", "Freq.[Hz]", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindowDesign", "Tab 1", Q_NULLPTR));
        checkBox_notch_2->setText(QApplication::translate("MainWindowDesign", "50 Hz", Q_NULLPTR));
        checkBox_high_2->setText(QApplication::translate("MainWindowDesign", "High Pass", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindowDesign", "Freq.[Hz]", Q_NULLPTR));
        checkBox_low_2->setText(QApplication::translate("MainWindowDesign", "Low Pass", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindowDesign", "Freq.[Hz]", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindowDesign", "Tab 2", Q_NULLPTR));
        groupBox_config->setTitle(QApplication::translate("MainWindowDesign", "Configuration Log", Q_NULLPTR));
        menu_File->setTitle(QApplication::translate("MainWindowDesign", "&App", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindowDesign: public Ui_MainWindowDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H

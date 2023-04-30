/**
 * @file /include/qt_ros/main_window.hpp
 *
 * @brief Qt based gui for qt_ros.
 *
 * @date November 2010
 **/
#ifndef qt_ros_MAIN_WINDOW_H
#define qt_ros_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtWidgets/QMainWindow>
#include <QtNetwork>
#include <QtCharts/QtCharts>
#include <atomic>
#include "ui_main_window.h"
#include "qnode.hpp"
#include "qt_ros/Packets.h"
#include "qnetstreamingreceiver.hpp"
#include "spuce/filters/notch_allpass.h"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace qt_ros {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();

	void closeEvent(QCloseEvent *event); // Overloaded function
	void showNoMasterMessage();
	// 初始化画布
	void InitDraw();
    // 初始化傅立叶变换的画布
//    void InitFFTDraw();
    // 初始化单个波形的画布
//    void InitSingleDraw();

public Q_SLOTS:
	/******************************************
	** Auto-connections (connectSlotsByName())
	*******************************************/
	void on_actionAbout_triggered();

private slots:
    // 连接Qt与仿真器
	void on_button_connect_clicked();
    // 初始化线条
	void InitLines(int lineNums);
    // 接收数据并绘制波形
	void RecvAndDraw(float* pfData, int nEegChan, long nNumSamples);
    // 更新日志消息
    void UpdateLogConfig();
	void UpdateLogCom();
	void UpdateLogEve();

    // 检测勾选框状态
	void on_checkBox_notch_stateChanged(int arg1);
	void on_checkBox_low_stateChanged(int arg1);
	void on_checkBox_high_stateChanged(int arg1);
	void on_checkBox_notch_2_stateChanged(int arg1);
    void on_checkBox_high_2_stateChanged(int arg1);
    void on_checkBox_low_2_stateChanged(int arg1);
    void on_tabWidget_currentChanged(int index);

private:
	Ui::MainWindowDesign ui;
	QNode qnode;

	QNetStreamingReceiver* m_qNetStreaming;
	BasicInfoAcq m_basicInfo;

	QChart* m_chart;
	QList<QSplineSeries*> m_spSeries;
    QList<QVector<QPointF>> data_show;
    int maxSize;
	QValueAxis* m_axisX;
	QValueAxis* m_axisY;
	int nNumChannels;
	double dDeltaY;
    double t_show;
	QThread* m_thread;

    QChart* m_fft_chart;
    QValueAxis* m_fft_axisX;
    QValueAxis* m_fft_axisY;

    QChart* m_single_chart;
    QValueAxis* m_single_axisX;
    QValueAxis* m_single_axisY;

	bool notch_check;
	bool hp_check;
	bool lp_check;
};

}  // namespace qt_ros

#endif // qt_ros_MAIN_WINDOW_H

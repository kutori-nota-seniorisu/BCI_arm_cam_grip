/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <QThread>
#include <iostream>
#include "../include/qt_ros/main_window.hpp"

// 添加信号处理文件
#include "spuce/filters/iir_coeff.h"
#include "spuce/filters/chebyshev_iir.h"
#include "spuce/filters/iir_df.h"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qt_ros
{

	using namespace Qt;

    /*****************************************************************************
	** Implementation [MainWindow]
	*****************************************************************************/

	MainWindow::MainWindow(int argc, char **argv, QWidget *parent)
		: QMainWindow(parent), qnode(argc, argv)
	{
		ui.setupUi(this);																	 // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
		QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application

		setWindowIcon(QIcon(":/images/icon.png"));
        QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

        /*********************
        ** Logging
        **********************/
//		QObject::connect(&qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingView()));

		// 构造新线程
		m_thread = new QThread();
		m_qNetStreaming = new QNetStreamingReceiver();
		m_qNetStreaming->moveToThread(m_thread);

		// 设置三个消息框
		ui.listView_config->setModel(m_qNetStreaming->LoggingConfigModel());
		ui.listView_com->setModel(m_qNetStreaming->LoggingComModel());
		ui.listView_eve->setModel(m_qNetStreaming->LoggingEveModel());

		// 启动线程
		connect(m_thread, SIGNAL(started()), m_qNetStreaming, SLOT(Run()));
        // 接收数据并绘制波形
//        connect(m_qNetStreaming, SIGNAL(SendData(float *, int, long)), this, SLOT(RecvAndDraw(float *, int, long)));
		// 通过节点发送采样频率
        connect(m_qNetStreaming, SIGNAL(SendRate(int)), &qnode, SLOT(QNode_Pub_Rate(int)));
		// 通过节点发送数据包
        connect(m_qNetStreaming, SIGNAL(SendData(float *, int, long)), &qnode, SLOT(QNode_Pub_Packet(float *, int, long)));
        // 初始化线条数量
//        connect(m_qNetStreaming, SIGNAL(SendChan(int)), this, SLOT(InitLines(int)));
		// 消息框滚动
		connect(m_qNetStreaming, SIGNAL(LoggingConfigUpdated()), this, SLOT(UpdateLogConfig()));
		connect(m_qNetStreaming, SIGNAL(LoggingComUpdated()), this, SLOT(UpdateLogCom()));
		connect(m_qNetStreaming, SIGNAL(LoggingEveUpdated()), this, SLOT(UpdateLogEve()));

        // 初始化画布
//        InitDraw();

        // 初始化滤波标志变量
		notch_check = ui.checkBox_notch->isChecked();
		lp_check = ui.checkBox_low->isChecked();
		hp_check = ui.checkBox_high->isChecked();
	}

	MainWindow::~MainWindow() {}

	/*****************************************************************************
	** Implementation [Slots]
	*****************************************************************************/

	void MainWindow::showNoMasterMessage()
	{
		QMessageBox msgBox;
		msgBox.setText("Couldn't find the ros master.");
		msgBox.exec();
		close();
	}

	/*****************************************************************************
	** Implemenation [Slots][manually connected]
	*****************************************************************************/

	/**
	 * This function is signalled by the underlying model. When the model changes,
	 * this will drop the cursor down to the last line in the QListview to ensure
	 * the user can always see the latest log message.
	 */
    // 更新日志消息
	void MainWindow::UpdateLogConfig()
	{
		ui.listView_config->scrollToBottom();
	}
	void MainWindow::UpdateLogCom()
	{
		ui.listView_com->scrollToBottom();
	}
	void MainWindow::UpdateLogEve()
	{
		ui.listView_eve->scrollToBottom();
	}

	/*****************************************************************************
	** Implementation [Menu]
	*****************************************************************************/

	void MainWindow::on_actionAbout_triggered()
	{
		QMessageBox::about(this, tr("About ..."), tr("<h2>PACKAGE_NAME Test Program 0.10</h2><p>Copyright Yujin Robot</p><p>This package needs an about description.</p>"));
	}

	/*****************************************************************************
	** Implementation [Configuration]
	*****************************************************************************/

	void MainWindow::closeEvent(QCloseEvent *event)
	{
		QMainWindow::closeEvent(event);
	}
	// 初始化画布
	void MainWindow::InitDraw()
	{
		// 初始化坐标轴与画布，并将画布设置到widget上
		m_axisX = new QValueAxis();
		m_axisY = new QValueAxis();
		m_chart = new QChart();
		ui.chartwidget->setChart(m_chart);

		m_chart->setTitleBrush(QBrush(QColor(0, 0, 0))); // 设置标题Brush
		m_chart->setTitleFont(QFont("微软雅黑"));		 // 设置标题字体
		m_chart->setTitle("曲线图");					 // 设置标题
		m_chart->legend()->hide();						 //隐藏图例
		m_chart->addAxis(m_axisX, Qt::AlignBottom);		 //设置坐标轴位于chart中的位置
		m_chart->addAxis(m_axisY, Qt::AlignLeft);

		m_axisX->setTitleText("x");
		m_axisX->setRange(0, 1);
		m_axisX->setGridLineVisible(false);

		m_axisY->setTitleText("y");
		m_axisY->setRange(0, 1);
		m_axisY->setGridLineVisible(false);
	}

    // 接收数据并绘制波形
    void MainWindow::RecvAndDraw(float *pfData, int nEegChan, long nNumSamples)
    {
        // 存放数据
        QVector<QVector<double>> packet(nEegChan, QVector<double>(nNumSamples));
        // 基线校准，并计算最大最小值
        float fSample;
        QVector<float> aMin;
        QVector<float> aMax;
        QVector<float> aAvg;

        aMin.resize(nEegChan);
        aMax.resize(nEegChan);
        aAvg.resize(nEegChan);

        // 获取最大值、最小值、平均值
        for (int i = 0; i < nEegChan; ++i)
        {
            aAvg[i] = 0.0f;
            for (int j = 0; j < nNumSamples; ++j)
            {
                fSample = pfData[j * nEegChan + i];
                if (j == 0)
                {
                    aMin[i] = fSample;
                    aMax[i] = fSample;
                }
                else
                {
                    if (fSample < aMin[i])
                        aMin[i] = fSample;
                    if (fSample > aMax[i])
                        aMax[i] = fSample;
                }

                aAvg[i] += fSample;
            }
            aAvg[i] /= nNumSamples;
            qDebug() << "sample " << i << " is " << pfData[i];
        }

        // 去除基线，并保存为二维数组形式
        for (int i = 0; i < nEegChan; ++i)
            for (int j = 0; j < nNumSamples; ++j)
                packet[i][j] = pfData[j * nEegChan + i] - aAvg[i];

        // 曲线绘制
//        for (int i = 0; i < nEegChan; ++i)
//        {
//            // 自适应范围
//            double dAutoScale = dDeltaY / ((aMax[i] - aMin[i]) * 1.25);
//            // 偏移量
//            double nYOffset = (i + 0.5) * dDeltaY;

//            // 检测是否数据量到上限
//            if (data_show[i].size() == maxSize)
//            {
//                data_show[i].remove(0, nNumSamples);

//                // 处理旧数据：横坐标减去一次样本数量的大小
//                QVector<QPointF>::iterator it;
//                for (it = data_show[i].begin(); it != data_show[i].end(); ++it)
//                    it->setX(it->x() - nNumSamples);
//            }

//            // 处理新数据
//            QVector<QPointF> aPoints;
//            aPoints.resize(nNumSamples);
//            for (int j = 0; j < nNumSamples; ++j)
//            {
//                aPoints[j].setX(j + data_show[i].size());
//                aPoints[j].setY(nYOffset + packet[i][j] * dAutoScale);
//            }

//            data_show[i].append(aPoints);

//            m_spSeries[i]->replace(data_show[i]);
//        }
//        qDebug() << "data_show:" << 0 << data_show[0].size();
        // 设置x轴刻度范围
//        m_axisX->setRange(0, data_show[0].size());
    }

    // 初始化线条
	void MainWindow::InitLines(int lineNums)
	{
        // 设置线条数量与y坐标间隔
		nNumChannels = lineNums;
		dDeltaY = 1.0 / nNumChannels;

		for (int i = 0; i < nNumChannels; ++i)
		{
			QSplineSeries *series = new QSplineSeries();
			m_spSeries.append(series);
			// 把曲线添加到画布上
			m_chart->addSeries(m_spSeries[i]);
			// 把坐标轴绑定到曲线上
			m_spSeries[i]->attachAxis(m_axisX);
			m_spSeries[i]->attachAxis(m_axisY);
			// 设置曲线颜色
			m_spSeries[i]->setColor(QColor(0, 0, 0));

            QVector<QPointF> points;
            data_show.append(points);
		}
	}
} // namespace qt_ros

// 连接Qt与仿真器
void qt_ros::MainWindow::on_button_connect_clicked()
{
	qnode.init();
//	QThread::sleep(2);
//	qDebug() << "Main wait 1 2s";
	QString sIP = ui.lineEdit_ip->text();
	QString sPort = ui.lineEdit_port->text();
	qDebug() << "Get connect" << sIP << "  " << sPort;

	if (m_qNetStreaming->IsConnected())
	{
		// stop netstreaming client
		m_qNetStreaming->SetClient(false);
		m_qNetStreaming->ClientRequestStreamData(false);
		m_qNetStreaming->CloseClient();
		m_thread->quit();
		ui.button_connect->setText("Connect");
	}
	else
	{
		// change some UI elements
		ui.button_connect->setText("Disconnect");

		// start netstreaming client
		m_qNetStreaming->SetClient(true, sIP, sPort.toInt());
		m_thread->start();
	}
}

void qt_ros::MainWindow::on_checkBox_notch_stateChanged(int arg1)
{
	notch_check = arg1;
}

void qt_ros::MainWindow::on_checkBox_low_stateChanged(int arg1)
{
	lp_check = arg1;
}

void qt_ros::MainWindow::on_checkBox_high_stateChanged(int arg1)
{
	hp_check = arg1;
}

void qt_ros::MainWindow::on_checkBox_notch_2_stateChanged(int arg1)
{
    notch_check = arg1;
}

void qt_ros::MainWindow::on_checkBox_high_2_stateChanged(int arg1)
{
    hp_check = arg1;
}

void qt_ros::MainWindow::on_checkBox_low_2_stateChanged(int arg1)
{
    lp_check = arg1;
}

void qt_ros::MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0)
    {
        notch_check = ui.checkBox_notch->isChecked();
        hp_check = ui.checkBox_high->isChecked();
        lp_check = ui.checkBox_low->isChecked();
    }
    else if (index == 1)
    {
        notch_check = ui.checkBox_notch_2->isChecked();
        hp_check = ui.checkBox_high_2->isChecked();
        lp_check = ui.checkBox_low_2->isChecked();
    }
}

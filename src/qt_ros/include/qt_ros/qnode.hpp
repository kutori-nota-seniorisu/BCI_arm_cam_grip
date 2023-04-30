/**
 * @file /include/qt_ros/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qt_ros_QNODE_HPP_
#define qt_ros_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <vector>
#include <QThread>
#include <QStringListModel>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qt_ros
{

	/*****************************************************************************
	** Class
	*****************************************************************************/

	class QNode : public QThread
	{
		Q_OBJECT
	public:
		QNode(int argc, char **argv);
		virtual ~QNode();
		bool init();

	Q_SIGNALS:
		void rosShutdown();

	private slots:
		// 发布采样频率
        void QNode_Pub_Rate(int);
		// 发布数据包
        void QNode_Pub_Packet(float *pfData, int nChannels, long nSamples);

	private:
		int init_argc;
		char **init_argv;
		// 发布者，发布采样频率
        ros::Publisher pub_rate;
		// 发布者，发布数据包
        ros::Publisher pub_packet;
	};

} // namespace qt_ros

#endif /* qt_ros_QNODE_HPP_ */

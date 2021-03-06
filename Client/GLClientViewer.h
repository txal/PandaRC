#pragma once

#include "Include/Logger/Logger.hpp"
#include "Common/Network/Protocol.h"

#include <QGLWidget>
#include "ui_GLClientViewer.h"

class GLClientViewer : public QGLWidget
{
	Q_OBJECT

public:
	GLClientViewer(QWidget *parent = Q_NULLPTR);
	~GLClientViewer();

public:
	void setUserID(int userID) { m_userID = userID;  }
	int getUserID() { return m_userID; }
	void setRoomID(int roomID) { m_roomID = roomID; }
	int getRoomID() { return m_roomID; }
	void onFrameSync(NSPROTO::FRAME_SYNC* proto);

protected:
	void paintEvent(QPaintEvent *event);
	void closeEvent(QCloseEvent *event);
	void initializeGL(); //初始化当前的opengl环境
	void resizeGL(int w, int h); //主要用来对渲染区域的高度和宽度进行一些变化处理

	void calcPointScale(double& scaleX, double& scaleY);
	void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);
	void mouseMoveEvent(QMouseEvent * event);
	void mouseDoubleClickEvent(QMouseEvent * event);
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent(QKeyEvent * event);

public slots:
	void onPaintDataChanged();

private:
	Ui::GLClientViewer ui;
	QWidget* m_parent;

	int m_userID;
	int m_roomID;

	QPixmap* m_pixmap;
	QPainter* m_painter;
};

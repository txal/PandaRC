#include "PandaRC.h"
#include <qpainter.h>
#include <qmath.h>

#include "log-writer/LogWriter.h"
#include "desktip-ipc/UpdateHandlerServer.h"

LogWriter glog;
UpdateHandlerServer* pHandlerSrv;


PandaRC::PandaRC(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//Logger::Instance()->Init();
	m_currFrame = NULL;
	m_oMyThread.start();
	m_pUDPNet = new UDPNet(parent);
	pHandlerSrv = new UpdateHandlerServer(this);
	connect(&m_oMyThread, SIGNAL(paintDataChanged(PDFRAME*)), this, SLOT(onPaintDataChanged(PDFRAME*)));
}

void PandaRC::onBtnSend()
{
}

void PandaRC::onBtnRecv()
{
}

void PandaRC::onPaintDataChanged(PDFRAME* pd)
{
	m_currFrame = pd;
	repaint(pd->rect.left, pd->rect.top, pd->rect.getWidth(), pd->rect.getHeight());
}

void PandaRC::paintEvent(QPaintEvent *event)
{
	if (m_currFrame == NULL) return;
	PDFRAME* pd = m_currFrame;
	Dimension dim = pd->fb.getDimension();
	uchar* pBuffer = (uchar*)pd->fb.getBuffer();
	int nBuffSize = pd->fb.getBufferSize();
	int nBytesRow = pd->fb.getBytesPerRow();
	QImage oImg(pBuffer, dim.width, dim.height, nBytesRow, QImage::Format_RGB32);
	QPainter painter(this);
	painter.drawImage(QPoint(pd->rect.left, pd->rect.top), oImg);
	delete pd;
	m_currFrame = NULL;

	//poDriver->grabFb();
	//HWND m_hWnd = (HWND)winId();
	//pScreenBuffer = poDriver->getScreenBuffer();
	//Dimension oDim = poDriver->getScreenDimension();
	//uchar* pBuffer = (uchar*)pScreenBuffer->getBuffer();
	//int nBuffSize = pScreenBuffer->getBufferSize();
	//int nBytesRow = pScreenBuffer->getBytesPerRow();
	//QImage oImg(pBuffer, oDim.width, oDim.height, nBytesRow, QImage::Format_RGB32);
	//printf("img is null: %d\n", oImg.isNull());
	//QPainter painter(this);
	//painter.drawImage(QPoint(0, 0), oImg);
}

//void PandaRC::onPaint(DeviceContext *dc, PAINTSTRUCT *paintStruct)
//{
//	Rect paintRect(&paintStruct->rcPaint);
//
//	if (paintRect.area() != 0) {
//		try {
//			AutoLock al(&m_bufferLock);
//			m_framebuffer.setTargetDC(paintStruct->hdc);
//			if (!m_clientArea.isEmpty()) {
//				doDraw(dc);
//			}
//		}
//		catch (const Exception &ex) {
//			m_logWriter->error(_T("Error in onPaint: %s"), ex.getMessage());
//		}
//	}
//}

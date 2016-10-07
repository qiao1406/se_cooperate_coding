# include <QTextCodec>
# include <QMessageBox>
# include <QElapsedTimer>
# include <windows.h>
# include "beijingsubway_co.h"
# include "Core.h"

BeijingSubway_co::BeijingSubway_co(QWidget *parent)
	: QMainWindow(parent)
{
	

	// to solve the problem of Garbled(乱码)
	QTextCodec *codec = QTextCodec::codecForName("GBK");

	ui.setupUi(this);
	//install event 
	ui.pushButton->installEventFilter(this);
	ui.pushButton_2->installEventFilter(this);

	// setup combo box
	ui.comboBox->addItems(QStringList(codec->toUnicode("途径最少")));
	ui.comboBox->addItems(QStringList(codec->toUnicode("换乘最少")));

	/*=================setup graphics view=======================*/
	QGraphicsScene *scene = new QGraphicsScene();
	ui.graphicsView->setScene(scene);
	//add station circle item
	QGraphicsTextItem *station_text;
	for (int i = 0; i < Core::stations.size(); i++) {
		QPen pen;
		pen.setWidth(2);
		Core::stations[i].station_circle->setPen(pen);
		scene->addItem(Core::stations[i].station_circle);
		//attention: to solve the problem of Garbled, use codec->toUnicode()
		station_text = scene->addText(codec->toUnicode(Core::stations[i].name.c_str()));
		station_text->setPos(Core::stations[i].x-3, Core::stations[i].y-3);
	}
	QPen pen;
	pen.setWidth(3);
	QGraphicsLineItem *l;
	//add line item
	for (int i = 0; i < Core::lines.size(); i++) {
		SLinkList tmp = Core::lines[i].head;
		pen.setColor(QColor(Core::lines[i].lineColor[0], Core::lines[i].lineColor[1], Core::lines[i].lineColor[2]));
		while (true) {
			//set the line between stations
			l = new QGraphicsLineItem();
			l->setLine(
				Core::stations[tmp->stationIndex].x,Core::stations[tmp->stationIndex].y,
				Core::stations[tmp->right->stationIndex].x,Core::stations[tmp->right->stationIndex].y);
			l->setPen(pen);
			scene->addItem(l);
			tmp = tmp->right;
			if (tmp->right == NULL || tmp== Core::lines[i].head) break;
		}
	}
	//add png picture
	QGraphicsPixmapItem *pixmap = new QGraphicsPixmapItem();
	pixmap->setPixmap(QPixmap("color.png"));
	pixmap->setPos(-800,-400);
	scene->addItem(pixmap);

	ui.graphicsView->show();

}

bool BeijingSubway_co::eventFilter(QObject *target, QEvent *event) {

	QTextCodec *codec = QTextCodec::codecForName("GBK");

	if (target == ui.pushButton && event->type() == QEvent::MouseButtonPress) {
		//button "查询" event
		string station_name1, station_name2;
		int station_id1, station_id2;
		station_name1 = codec->fromUnicode(ui.textEdit->toPlainText());
		station_name2 = codec->fromUnicode(ui.textEdit_2->toPlainText());
		if (station_name1.size()==0 && station_name2.size()==0) 
			return QMainWindow::eventFilter(target, event);
		station_id1 = -1;
		station_id2 = -1;
		for (int i = 0; i < Core::stations.size(); i++) {
			if (Core::stations[i].name == station_name1) station_id1 = i;
			if (Core::stations[i].name == station_name2) station_id2 = i;
			if (station_id1 != -1 && station_id2 != -1) break;
		}
		if (station_id1 == -1 || station_id2 == -1)
			QMessageBox::information(this, "error", codec->toUnicode("站点名称有误"));
		else {
			BeijingSubway_co::resetGraphicView();
			vector<int> result = (ui.comboBox->currentIndex() == 0)?Core::SPath(station_id1,station_id2):Core::LTPath(station_id1,station_id2);
			QBrush green_brush, blue_brush;
			green_brush.setColor(QColor(0, 255, 0));
			green_brush.setStyle(Qt::SolidPattern);
			blue_brush.setColor(QColor(0, 0, 255));
			blue_brush.setStyle(Qt::SolidPattern);
			for (int i = 0; i < result.size(); i++) {
				Core::stations[result[i]].station_circle->setBrush(blue_brush);
				ui.label_4->setText(codec->toUnicode(Core::stations[result[i]].name.c_str()));
				QElapsedTimer t;
				t.start();
				while (t.elapsed() < 1000)
					QCoreApplication::processEvents();
				Core::stations[result[i]].station_circle->setBrush(green_brush);
			}
		}
	}
	if (target == ui.pushButton_2 && event->type() == QEvent::MouseButtonPress) {
		//button "重置" event
		BeijingSubway_co::resetGraphicView();
	}

	return QMainWindow::eventFilter(target, event);
}

void BeijingSubway_co::resetGraphicView() {
	QBrush brush;
	brush.setColor(QColor(255, 255, 255));
	brush.setStyle(Qt::SolidPattern);
	for (int i = 0; i < Core::stations.size(); i++) {
		Core::stations[i].station_circle->setBrush(brush);
	}
	ui.label_4->setText("");
}

BeijingSubway_co::~BeijingSubway_co()
{

}

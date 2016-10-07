#ifndef BEIJINGSUBWAY_CO_H
#define BEIJINGSUBWAY_CO_H

#include <QtWidgets/QMainWindow>
#include "ui_beijingsubway_co.h"

class BeijingSubway_co : public QMainWindow
{
	Q_OBJECT

public:
	BeijingSubway_co(QWidget *parent = 0);
	//reload function
	bool eventFilter(QObject *target, QEvent *event);
	//my function
	void resetGraphicView();
	~BeijingSubway_co();

private:
	Ui::BeijingSubway_coClass ui;
};

#endif // BEIJINGSUBWAY_CO_H

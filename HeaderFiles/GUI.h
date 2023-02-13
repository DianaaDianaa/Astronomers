#pragma once
#include "Service.h"
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qlayout.h>
#include <qtableview.h>
#include <qcheckbox.h>
#include <qlabel.h>


class GUI : public QWidget
{
	QOBJECT_H
private:
	Service service;
	int index;
	QListWidget* starsList;
	QCheckBox* checkBox;
	QCheckBox* checkBox2;
	QPushButton* addButton;
	QPushButton* updateNameButton;
	QPushButton* updateRaButton;
	QPushButton* updateDecButton;
	QPushButton* updateDiamButton;
	QLineEdit* nameLineEdit;
	QLineEdit* raLineEdit;
	QLineEdit* decLineEdit;
	QLineEdit* diameterLineEdit;
	QLineEdit* newNameLE;
	QLineEdit* newRaLE;
	QLineEdit* newDecLE;
	QLineEdit* newDiamLE;
public:
	GUI(Service service_, int i, QWidget* parent = 0);
	void init();
	void populate();
	void connect();
	void showConstellation();
	void add();
	void updateName();
	void updateRa();
	void updateDec();
	void updateDiam();
};
#include "GUI.h"

GUI::GUI(Service service_, int i, QWidget* parent)
{
	service = service_;
	index = i;
	init();
	populate();
	connect();
}

void GUI::init()
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	//list
	QVBoxLayout* listLayout = new QVBoxLayout();
	starsList = new QListWidget();
	listLayout->addWidget(starsList);

	//attributes
	QVBoxLayout* attributesLayout = new QVBoxLayout();
	nameLineEdit = new QLineEdit();
	raLineEdit = new QLineEdit();
	decLineEdit = new QLineEdit();
	diameterLineEdit = new QLineEdit();
	newNameLE = new QLineEdit();
	newRaLE = new QLineEdit();
	newDecLE = new QLineEdit();
	newDiamLE = new QLineEdit();
	QLabel* nameLabel = new QLabel("name");
	QLabel* raLabel = new QLabel("right ascension");
	QLabel* decLabel = new QLabel("declination");
	QLabel* diameterLabel = new QLabel("diameter");
	QLabel* newNameLabel = new QLabel("new name");
	QLabel* newRaLAbel = new QLabel("new ra");
	QLabel* newDecLabel = new QLabel("new dec");
	QLabel* newDiamLabel = new QLabel("new diameter");
	nameLabel->setBuddy(nameLineEdit);
	raLabel->setBuddy(raLineEdit);
	decLabel->setBuddy(decLineEdit);
	diameterLabel->setBuddy(diameterLineEdit);
	newNameLabel->setBuddy(newNameLE);
	newRaLAbel->setBuddy(newRaLE);
	newDecLabel->setBuddy(newDecLE);
	newDiamLabel->setBuddy(newDiamLE);
	attributesLayout->addWidget(nameLabel);
	attributesLayout->addWidget(nameLineEdit);
	attributesLayout->addWidget(raLabel);
	attributesLayout->addWidget(raLineEdit);
	attributesLayout->addWidget(decLabel);
	attributesLayout->addWidget(decLineEdit);
	attributesLayout->addWidget(diameterLabel);
	attributesLayout->addWidget(diameterLineEdit);
	attributesLayout->addWidget(newNameLabel);
	attributesLayout->addWidget(newNameLE);
	attributesLayout->addWidget(newRaLAbel);
	attributesLayout->addWidget(newRaLE);
	attributesLayout->addWidget(newDecLabel);
	attributesLayout->addWidget(newDecLE);
	attributesLayout->addWidget(newDiamLabel);
	attributesLayout->addWidget(newDiamLE);


	//buttons
	QHBoxLayout* buttonsLayout = new QHBoxLayout();
	checkBox = new QCheckBox("Click");
	buttonsLayout->addWidget(checkBox);
	checkBox2 = new QCheckBox("Unclick");
	buttonsLayout->addWidget(checkBox2);
	addButton = new QPushButton("add");
	buttonsLayout->addWidget(addButton);
	updateNameButton = new QPushButton("update name");
	updateRaButton = new QPushButton("update ra");
	updateDecButton = new QPushButton("update dec");
	updateDiamButton = new QPushButton("update diameter");
	buttonsLayout->addWidget(updateNameButton);
	buttonsLayout->addWidget(updateRaButton);
	buttonsLayout->addWidget(updateDecButton);
	buttonsLayout->addWidget(updateDiamButton);

	//set them up
	mainLayout->addLayout(listLayout);
	mainLayout->addLayout(attributesLayout);
	mainLayout->addLayout(buttonsLayout);
}

void GUI::populate()
{
	starsList->clear();
	vector<Star> stars = service.sortByConstellation();
	for (auto s : stars)
	{
		string starStr = s.toStd();
		QString starQstr = QString::fromStdString(starStr);
		QListWidgetItem* item = new QListWidgetItem(starQstr);
		starsList->addItem(item);
	}
}

void GUI::connect()
{
	QObject::connect(checkBox, &QCheckBox::clicked, this, &GUI::showConstellation);
	//QObject::connect(checkBox, &QCheckBox::isChecked, this, &GUI::showConstellation);
	QObject::connect(checkBox2, &QCheckBox::clicked, this, &GUI::populate);
	QObject::connect(addButton, &QPushButton::clicked, this, &GUI::add);
	QObject::connect(updateNameButton, &QPushButton::clicked, this, &GUI::updateName);
	QObject::connect(updateRaButton, &QPushButton::clicked, this, &GUI::updateRa);
	QObject::connect(updateDecButton, &QPushButton::clicked, this, &GUI::updateDec);
	QObject::connect(updateDiamButton, &QPushButton::clicked, this, &GUI::updateDiam);
}

void GUI::showConstellation()
{
	string constellation = service.getAstronomers()[index].getConstellation();
	starsList->clear();
	vector<Star> stars = service.showConstellation(constellation);
	for (auto s : stars)
	{
		string starStr = s.toStd();
		QString starQstr = QString::fromStdString(starStr);
		QListWidgetItem* item = new QListWidgetItem(starQstr);
		starsList->addItem(item);
	}

}

void GUI::add()
{
	QString nameQ = nameLineEdit->text();
	QString raQ = raLineEdit->text();
	QString decQ = decLineEdit->text();
	QString diameterQ = diameterLineEdit->text();

	string name = nameQ.toStdString();
	string constel = service.getAstronomers()[index].getConstellation();
	string raS = raQ.toStdString();
	string decS = decQ.toStdString();
	string diamS = diameterQ.toStdString();

	try
	{
		int ra = stoi(raS);
		int dec = stoi(decS);
		int diam = stoi(diamS);
		service.addStar(name, constel, ra, dec, diam);
		service.save_to_file();
	}
	catch (...)
	{
		nameLineEdit->clear();
		raLineEdit->clear();
		decLineEdit->clear();
		diameterLineEdit->clear();
		QMessageBox msgBox;
		msgBox.setText("error");
		msgBox.exec();
		return;
	}

	nameLineEdit->clear();
	raLineEdit->clear();
	decLineEdit->clear();
	diameterLineEdit->clear();
	populate();

}

void GUI::updateName()
{
	QString nameQ = nameLineEdit->text();
	QString newNameQ = newNameLE->text();
	string name = nameQ.toStdString();
	string newName = newNameQ.toStdString();
	try
	{
		service.updateName(newName, name);
		service.save_to_file();
	}
	catch (...)
	{
		nameLineEdit->clear();
		newNameLE->clear();
		QMessageBox msgBox;
		msgBox.setText("error");
		msgBox.exec();
		return;
	}
	nameLineEdit->clear();
	newNameLE->clear();
	populate();
}

void GUI::updateRa()
{
	QString nameQ = nameLineEdit->text();
	QString raQ = newRaLE->text();
	string name = nameQ.toStdString();
	string raS = raQ.toStdString();
	try
	{
		int ra = stoi(raS);
		service.updateRa(ra, name);
		service.save_to_file();
	}
	catch (...)
	{
		nameLineEdit->clear();
		newRaLE->clear();
		QMessageBox msgBox;
		msgBox.setText("error");
		msgBox.exec();
		return;
	}
	nameLineEdit->clear();
	newRaLE->clear();
	populate();
}

void GUI::updateDec()
{
	QString nameQ = nameLineEdit->text();
	QString decQ = newDecLE->text();
	string name = nameQ.toStdString();
	string decS = decQ.toStdString();
	try
	{
		int dec = stoi(decS);
		service.updateDec(dec, name);
		service.save_to_file();
	}
	catch (...)
	{
		nameLineEdit->clear();
		newDecLE->clear();
		QMessageBox msgBox;
		msgBox.setText("error");
		msgBox.exec();
		return;
	}
	nameLineEdit->clear();
	newDecLE->clear();
	populate();
}

void GUI::updateDiam()
{
	QString nameQ = nameLineEdit->text();
	QString dQ = newDiamLE->text();
	string name = nameQ.toStdString();
	string dS = dQ.toStdString();
	try
	{
		int d = stoi(dS);
		service.updateDiameter(d, name);
		service.save_to_file();
	}
	catch (...)
	{
		nameLineEdit->clear();
		newDiamLE->clear();
		QMessageBox msgBox;
		msgBox.setText("error");
		msgBox.exec();
		return;
	}
	nameLineEdit->clear();
	newDiamLE->clear();
	populate();
}

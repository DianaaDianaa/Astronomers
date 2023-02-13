#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "GUI.h"

int main(int argc, char *argv[])
{
    Service serv;

    QApplication a(argc, argv);
    
    int i = 0;
    vector<Astronomer> astronomers = serv.getAstronomers();
    while (i < astronomers.size())
    {
        string name = astronomers[i].getName();
        QString nameQstr = QString::fromStdString(name);
        GUI* gui = new GUI(serv, i);
        gui->setWindowTitle(nameQstr);
        gui->show();
        i++;
    }

    return a.exec();
}

#include <QtGui/QApplication>

#include "gui/CMainForm.hpp"


int main(int argc, char **argv) {
	QApplication app(argc, argv);

	QTranslator qtTranslator;
	qtTranslator.load("kboy_" + QLocale::system().name(), QDir::homePath()+"/.kboy/lang");
	app.installTranslator(&qtTranslator);

	CMainForm dlg;
	dlg.show();

	return app.exec();
}

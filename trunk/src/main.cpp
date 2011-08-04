#include <QtGui/QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QDir>
#include <QLocale>

#include "gui/CMainForm.hpp"


int main(int argc, char **argv) {
   QApplication app(argc, argv);

   QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));

   QTranslator qtTranslator;
   qtTranslator.load("kboy_" + QLocale::system().name(), "/home/thomas/src/kboy/build/");
   app.installTranslator(&qtTranslator);

   CMainForm dlg;
   dlg.show();

   return app.exec();
}

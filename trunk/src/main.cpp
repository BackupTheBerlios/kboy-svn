/*
 * KBoy is a graphical user interface for managing a collection of Gameboy
 * ROM files and assigning emulator configuration information to them.
 *
 * Copyright (C) 2011  Thomas Wesenigk <thomas_aus_dresden@web.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <QtGui/QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QDir>
#include <QLocale>
#include <QTextStream>

#include "gui/CMainForm.hpp"


#define VERSIONNUMBER "0.2"


void printSplash() {
   QTextStream out(stdout);
   out << "This is KBoy version " << VERSIONNUMBER << "\n\n";
   out << "This program is free software; you can redistribute it and/or modify\n" \
          "it under the terms of the GNU General Public License.\n";
   out << "This program is distributed in the hope that it will be useful\n" \
          "and comes without any warranty.\n\n";
   out << "Copyright 2010-2011 by Thomas Wesenigk\n\n";
}



int main(int argc, char **argv) {
   // TODO: Print out some splash message and author names, program version etc.
   QApplication app(argc, argv);

   printSplash();

   QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));

   QTranslator qtTranslator;
   qtTranslator.load("kboy_" + QLocale::system().name(), "/home/thomas/src/kboy/build/");
   app.installTranslator(&qtTranslator);

   CMainForm dlg;
   dlg.show();

   return app.exec();
}

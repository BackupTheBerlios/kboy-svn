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

#include <QtDebug>

#include <CGame.hpp>

#include "CXmlGameListWriter.hpp"


CXmlGameListWriter::CXmlGameListWriter(const QString& filename) :
      m_Filename(filename) {}


void CXmlGameListWriter::writeGameList(CGameListModel* gamelist) const {
   // Save the whole game list as XML into the file defined by the constructor
   QList<CGame>::const_iterator iter = gamelist->getInternalGameList().begin();

   // Open the XML file for writing (create it if necessary)
   QFile* xmlFile = new QFile(m_Filename);
   if (xmlFile->open(QIODevice::WriteOnly) == true) {
      // Create and configure a new QXmlStreamWriter
      QXmlStreamWriter xmlWriter(xmlFile);
      xmlWriter.setAutoFormatting(true);
      xmlWriter.setAutoFormattingIndent(6);
      // serialize the whole game list into the XML stream
      xmlWriter.writeStartDocument("1.0");
      xmlWriter.writeStartElement("gamelist");
      // Loop through the whole gamelist and write each game block separately
      for (;iter != gamelist->getInternalGameList().end();++iter) {
         xmlWriter.writeStartElement("game");
         xmlWriter.writeAttribute("name", iter->getName());
         xmlWriter.writeAttribute("romfile", iter->getFilename());
         // Write the game block with specific options
         writeGameBlock(xmlWriter, *iter);
         xmlWriter.writeEndElement();
      }
      xmlWriter.writeEndElement();
      xmlWriter.writeEndDocument();
      xmlFile->close();
   }
   else {
      // Cannot open file
      return;
      // TODO: Throw exception
   }
}


void CXmlGameListWriter::writeGameBlock(QXmlStreamWriter& xmlWriter, const CGame& game) const {
   // Write game options into the XML stream
   xmlWriter.writeStartElement("options");
   // Attribute "emutype"
   switch (game.getOptions().getEmulator()) {
      case CAbstractEmulatorOptions::GNUBOY:
         xmlWriter.writeAttribute("emutype", "gnuboy");
         // write all gnuboy options
         writeGnuboyOptions(xmlWriter, reinterpret_cast<const CGnuboyOptions&>(game.getOptions()));
         break;
      case CAbstractEmulatorOptions::VBA:
         xmlWriter.writeAttribute("emutype", "vba");
         // write all VBA options
         writeVbaOptions(xmlWriter, reinterpret_cast<const CVBAOptions&>(game.getOptions()));
         break;
      default:
         // Something is really broken here (should actually not happen)!
         qDebug() << "[Error] Unkown emulator type in writeGameBlock()!\n";
         // TODO throw an exception
   }

   xmlWriter.writeEndElement(); // options
}



void CXmlGameListWriter::writeVbaOptions(QXmlStreamWriter& xmlWriter, const CVBAOptions& options) const {
   // shell command to start the emulator
   xmlWriter.writeTextElement("commandline", options.getEmuCommand());
   // fullscreen mode
   if (true == options.getFullscreen()) {
      xmlWriter.writeTextElement("fullscreen", "true");
   }
   else {
      xmlWriter.writeTextElement("fullscreen", "false");
   }
   // graphics scaling factor
   xmlWriter.writeTextElement("scale", QString::number(options.getScale()));
}


void CXmlGameListWriter::writeGnuboyOptions(QXmlStreamWriter& xmlWriter, const CGnuboyOptions& options) const {
   // emulator start command
   xmlWriter.writeTextElement("commandline", options.getEmuCommand());
   // fullscreen mode
   if (true == options.getFullscreen()) {
      xmlWriter.writeTextElement("fullscreen", "true");
   }
   else {
      xmlWriter.writeTextElement("fullscreen", "false");
   }
   // sound
   if (true == options.getSound()) {
      xmlWriter.writeTextElement("sound", "true");
   }
   else {
      xmlWriter.writeTextElement("sound", "false");
   }
   // hardware acceleration
   if (true == options.getHardwareAccl()) {
      xmlWriter.writeTextElement("hardwareaccl", "true");
   }
   else {
      xmlWriter.writeTextElement("hardwareaccl", "false");
   }
   // graphics scaling factor
   xmlWriter.writeTextElement("scale", QString::number(options.getScale()));
}

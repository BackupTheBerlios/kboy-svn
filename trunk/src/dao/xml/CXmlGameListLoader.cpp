/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  thw <thomas@fomori.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <memory>

#include "emulators/gnuboy/CGnuboyOptions.hpp"
#include "emulators/vba/CVBAOptions.hpp"

#include "CXmlGameListLoader.hpp"


CXmlGameListLoader::CXmlGameListLoader(const QString& fileName)
   : m_XmlFileName(fileName)
{
}

unsigned int CXmlGameListLoader::readGameList(CGameListModel* gamelist) {
   // Read a game list from the XML data source and append it to the input "gamelist".
   // With this structure, even on error (exception thrown by this method) the game list can be used (even it may be empty)
   unsigned int gameCounter=0; // Count the number of games we added to the game list

   // Try to open the XML file if it exists
   if (!QFile::exists(m_XmlFileName)) {
      // File doesn't exist
      return 0;
      //TODO throw exception
   }
   QFile *xmlFile=new QFile(m_XmlFileName);
   if(!xmlFile->open(QIODevice::ReadOnly)) {
      // Cannot open the file
      return 0;
      // TODO: Throw an exception
   }

   // Create XmlStreamReader to read XML data from the now opened file
   QXmlStreamReader xmlReader(xmlFile);

   // The file has to start with the document start tag ^^
   xmlReader.readNext();
   if (!xmlReader.isStartDocument()) {
      xmlFile->close();
      return false;
   }
   // After that, gamelist start follows
   xmlReader.readNext();
   if (!xmlReader.isStartElement() || (xmlReader.qualifiedName().toString() != "gamelist")) {
      xmlFile->close();
      return false;
   }

   // Read all game descriptions from the following list of <game>s
   // This is a small and simple parser that reads as much data as possible without bothering about them to be valid.
   while (!xmlReader.atEnd()) {
      xmlReader.readNext();

      if (xmlReader.isStartElement() && xmlReader.qualifiedName().toString()=="game") {   // Start of a <game />
         // Create new game object with ROM file path stored in the <game> tag
         m_NewGame.reset(new CGame(xmlReader.attributes().value("romfile").toString()));
         // Set the name of the game entry (set by the user) that is also stored in the <game> tag
         m_NewGame->setName(xmlReader.attributes().value("name").toString());
         // Read the whole game data set from the file
         readGameBlock(xmlReader); // May throw an exception on error!
         // TODO: We should continue with the next game on exception (instead on ending...)
      }
      else if ((xmlReader.isEndElement() && xmlReader.qualifiedName().toString()=="game")) {
         // Successfully read the game information -> append it to the game list
         gamelist->addItem(*m_NewGame);
         gameCounter++;
         m_NewGame.reset(0); // Delete the game object
      }
      else if ((xmlReader.isEndElement() && xmlReader.qualifiedName().toString()=="gamelist") || xmlReader.isEndDocument()) {
         // document end
         break;
      }
      // Unrecognised tags will simply be ignored...
   }

   // Close the input file
   xmlFile->close();
}

void CXmlGameListLoader::readGameBlock(QXmlStreamReader& xmlReader) const {
   /* Read all information about a game (options etc.) */
   while (!xmlReader.atEnd()) {
      xmlReader.readNext();

      if (xmlReader.isStartElement() && xmlReader.qualifiedName().toString()=="options") {
         // Which emulator should be used for this game?
         if (xmlReader.attributes().value("emutype").toString()=="gnuboy") {
            // Set emulator type to GnuBoy and read the gnuboy options from XML
            m_NewGame->changeEmulator(CAbstractEmulatorOptions::GNUBOY);
            m_NewGame->setOptions(readGnuboyOptions(xmlReader));
            // Any thrown exception will be forwarded to the caller
         }
         else if (xmlReader.attributes().value("emutype").toString()=="vba") {
            // Set emulator type to VBA and read the options from XML
            m_NewGame->changeEmulator(CAbstractEmulatorOptions::VBA);
            m_NewGame->setOptions(readVbaOptions(xmlReader));
            // Any thrown exception will be forwarded to the caller
         }
         else {
            // Unknown emulator
            return;
            // TODO: Throw an exception!
         }
         break; // Break the loop after we successfully read the game tag
      }
   }
}



std::auto_ptr<CAbstractEmulatorOptions> CXmlGameListLoader::readVbaOptions(QXmlStreamReader& xmlReader) const {
   /* Read the stored options for the VBA emulator */
   // The constructor defines a set of standard options. They will be used if nothing is redefined in the XML file for an option
   CVBAOptions options;

   while (!xmlReader.atEnd()) {
      xmlReader.readNext();

      if (xmlReader.isStartElement()) {
         if (xmlReader.qualifiedName().toString()=="commandline") {
            // shell command to start the emulator
            options.setEmuCommand(xmlReader.readElementText());
         }
         else if (xmlReader.qualifiedName().toString()=="fullscreen") {
            // enable full screen mode?
            if (xmlReader.readElementText()=="true") options.setFullscreen(true);
            else options.setFullscreen(false);
         }
         else if (xmlReader.qualifiedName().toString()=="scale") {
            // set the scale factor for graphical output
            options.setScale(xmlReader.readElementText().toShort());
         }
      }
      else if (xmlReader.isEndElement() && xmlReader.qualifiedName().toString()=="options") {
         // We reached the end of the options block --> break the loop
         break;
      }
   }
   return std::auto_ptr<CAbstractEmulatorOptions>(new CVBAOptions(options));
}

// TODO: The options must be deleted some time...
std::auto_ptr<CAbstractEmulatorOptions> CXmlGameListLoader::readGnuboyOptions(QXmlStreamReader& xmlReader) const {
   /* Read the stored options for the GnuBoy emulator */
   // The constructor defines a set of standard options. They will be used if nothing is redefined in the XML file for an option
   CGnuboyOptions options;

   // Read all options and store them in the options object
   while (!xmlReader.atEnd()) {
      xmlReader.readNext();

      if (xmlReader.isStartElement()) {
         if (xmlReader.qualifiedName().toString()=="commandline") {
            // shell command to start the emulator
            options.setEmuCommand(xmlReader.readElementText());
         }
         else if (xmlReader.qualifiedName().toString()=="fullscreen") {
            // enable full screen mode?
            if (xmlReader.readElementText()=="true") options.setFullscreen(true);
            else options.setFullscreen(false);
         }
         else if (xmlReader.qualifiedName().toString()=="sound") {
            // enable sound output?
            if (xmlReader.readElementText()=="true") options.setSound(true);
            else options.setSound(false);
         }
         else if (xmlReader.qualifiedName().toString()=="hardwareaccl") {
            // enable hardware acceleration?
            if (xmlReader.readElementText()=="true") options.setHardwareAccl(true);
            else options.setHardwareAccl(false);
         }
         else if (xmlReader.qualifiedName().toString()=="scale") {
            // set the scale factor for graphical output
            options.setScale(xmlReader.readElementText().toShort());
         }
      }
      else if (xmlReader.isEndElement() && xmlReader.qualifiedName().toString()=="options") {
         // We reached the end of the options block --> break the loop
         break;
      }
   }
   return std::auto_ptr<CAbstractEmulatorOptions>(new CGnuboyOptions(options));
}

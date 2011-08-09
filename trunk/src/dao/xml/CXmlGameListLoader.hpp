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

#ifndef CXMLGAMELISTLOADER_HPP
#define CXMLGAMELISTLOADER_HPP

#include <memory>

#include <QString>
#include <QXmlStreamReader>

#include "CGameListModel.hpp"
#include "emulators/CAbstractEmulatorOptions.hpp"
#include "dao/IAbstractGameListLoader.hpp"

class CXmlGameListLoader : public IAbstractGameListLoader {
public:

   virtual ~CXmlGameListLoader() {}

   CXmlGameListLoader(const QString& fileName);

   unsigned int readGameList(CGameListModel* gamelist);

private:
   QString m_XmlFileName;
   std::auto_ptr<CGame> m_NewGame;

   void readGameBlock(QXmlStreamReader& xmlReader) const;


   std::auto_ptr<CAbstractEmulatorOptions> readVbaOptions(QXmlStreamReader& xmlReader) const;
   std::auto_ptr<CAbstractEmulatorOptions> readGnuboyOptions(QXmlStreamReader& xmlReader) const;
};

#endif // CXMLGAMELISTLOADER_HPP

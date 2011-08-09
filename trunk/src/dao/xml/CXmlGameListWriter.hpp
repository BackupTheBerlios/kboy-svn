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

#ifndef CXMLGAMELISTWRITER_HPP
#define CXMLGAMELISTWRITER_HPP

#include <QString>
#include <QXmlStreamWriter>

#include "CGame.hpp"
#include "CGameListModel.hpp"
#include "emulators/gnuboy/CGnuboyOptions.hpp"
#include "emulators/vba/CVBAOptions.hpp"
#include <dao/IAbstractGameListWriter.hpp>


class CXmlGameListWriter : public IAbstractGameListWriter {

public:
   virtual void writeGameList(CGameListModel* gamelist) const;
   CXmlGameListWriter(const QString& filename);


private:
   QString m_Filename;


   void writeGameBlock(QXmlStreamWriter& xmlWriter, const CGame& game) const;
   void writeVbaOptions(QXmlStreamWriter& xmlWriter, const CVBAOptions& options) const;
   void writeGnuboyOptions(QXmlStreamWriter& xmlWriter, const CGnuboyOptions& options) const;
};

#endif // CXMLGAMELISTWRITER_HPP

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

#include "emulators/vba/CVBAOptionsWidget.hpp"


CVBAOptionsWidget::CVBAOptionsWidget(CVBAOptions& emulatorOptions, QWidget *parent)
      : QWidget(parent)
      , m_Options(emulatorOptions)
{
   // Initialize all GUI elements
   OptionenVBox = new QVBoxLayout();
   ScaleBox = new QWidget();
   ScaleHBox = new QFormLayout();
   CheckFullscreen = new QCheckBox(trUtf8("full screen"));
   SpinScale = new QSpinBox();
   CmdLineHBox = new QFormLayout();
   CmdLineBox = new QWidget();
   EditCmdLine = new QLineEdit();

   // create all GUI elements
   // "graphics scale" input
   ScaleHBox->addRow(trUtf8("graphics scaling:"), SpinScale);
   ScaleBox->setLayout(ScaleHBox);
   // "command line" input
   CmdLineHBox->addRow(trUtf8("shell command:"), EditCmdLine);
   CmdLineBox->setLayout(CmdLineHBox);
   // "main" widget
   OptionenVBox->addWidget(CmdLineBox);
   OptionenVBox->addSpacing(10);
   OptionenVBox->addWidget(CheckFullscreen);
   OptionenVBox->addWidget(ScaleBox);
   this->setLayout(OptionenVBox);

   // configure all GUI elements
   SpinScale->setRange(1, 4);
   SpinScale->setSingleStep(1);

   // Set all current option values
   CheckFullscreen->setCheckState(m_Options.getFullscreen() == true ? Qt::Checked : Qt::Unchecked);
   SpinScale->setValue(m_Options.getScale());
   EditCmdLine->setText(m_Options.getEmuCommand());

   // connect all events
   connect(CheckFullscreen, SIGNAL(stateChanged(int)), this, SLOT(fullscreenChanged(int)));
   connect(SpinScale, SIGNAL(valueChanged(int)), this, SLOT(scaleChanged(int)));
   connect(EditCmdLine, SIGNAL(textEdited(const QString&)), this, SLOT(cmdlineChanged(const QString&)));
}




void CVBAOptionsWidget::fullscreenChanged(int state) {
   m_Options.setFullscreen(state == Qt::Checked ? true : false);
}


void CVBAOptionsWidget::scaleChanged(int scale) {
   m_Options.setScale(scale);
}

void CVBAOptionsWidget::cmdlineChanged(const QString& text) {
   m_Options.setEmuCommand(text);
}



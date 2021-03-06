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

#include <QDebug>

#include "dao/xml/CXmlGameListLoader.hpp"
#include "dao/xml/CXmlGameListWriter.hpp"
#include "emulators/CAbstractEmulatorOptions.hpp"

#include "gui/CMainForm.hpp"

void CMainForm::initWidgets() {
   // Initialize all widgets
   // layout objects
   m_MainHBox = new QHBoxLayout();
   m_GamesButtonHBox = new QHBoxLayout();
   m_GamesFrameBox = new QVBoxLayout();
   m_RechtsVBox = new QVBoxLayout();
   m_OptionsVBox = new QVBoxLayout();

   // container objects
   m_FrameGamesList = new QGroupBox(trUtf8("Games"));
   m_FrameOptions = new QGroupBox(trUtf8("Emulator configuration"));
   m_GamesFrameButtonBox = new QWidget();
   m_BoxRight = new QWidget();


   // control widgets
   m_ButtonAdd = new QPushButton(trUtf8("Add new"));
   m_ButtonDel = new QPushButton(trUtf8("Remove"));
   m_ButtonStart = new QPushButton(trUtf8("Start game"));
   m_ButtonEnde = new QPushButton(trUtf8("Quit"));
   m_ListViewGames = new QTableView();
   m_ComboEmulator = new QComboBox();
}


void CMainForm::buildGUI() {
   // build the actual GUI

   /* left frame (game list) */
   // buttons at the bottom
   m_GamesButtonHBox->addWidget(m_ButtonAdd);
   m_GamesButtonHBox->addWidget(m_ButtonDel);
   m_GamesFrameButtonBox->setLayout(m_GamesButtonHBox);
   // games frame
   m_GamesFrameBox->addWidget(m_ListViewGames);
   m_GamesFrameBox->addWidget(m_GamesFrameButtonBox);
   m_FrameGamesList->setLayout(m_GamesFrameBox);

   /* right frame (options & buttons) */
   // options widget
   m_OptionsVBox->addWidget(m_ComboEmulator);
   m_OptionsVBox->addSpacing(15);
   /* end of emulator options */

   // controlling buttons at the bottom
   m_FrameOptions->setLayout(m_OptionsVBox);
   m_RechtsVBox->addWidget(m_FrameOptions);
   m_RechtsVBox->addWidget(m_ButtonStart);
   m_RechtsVBox->addSpacing(10);
   m_RechtsVBox->addWidget(m_ButtonEnde);
   m_BoxRight->setLayout(m_RechtsVBox);

   /* main layout */
   m_MainHBox->addWidget(m_FrameGamesList);
   m_MainHBox->addWidget(m_BoxRight);
   this->setLayout(m_MainHBox);
}


void CMainForm::configureWidgets() {
   // configure all widgets
   m_MainHBox->setStretchFactor(m_FrameGamesList, 2);

   m_ListViewGames->setModel(m_GameList);
   m_ListViewGames->verticalHeader()->hide();
   m_ListViewGames->setWordWrap(false);
   m_ListViewGames->resizeColumnsToContents();
   m_ListViewGames->resizeRowsToContents();
   m_ListViewGames->setEditTriggers(QAbstractItemView::NoEditTriggers);
   m_ListViewGames->setSelectionMode(QAbstractItemView::SingleSelection);
   m_ListViewGames->setSelectionBehavior(QAbstractItemView::SelectRows);

   m_FrameOptions->setEnabled(false);

   this->setMinimumSize(QSize(this->width(), this->height()));
   //this->setMinimumWidth(this->width());

   // The ordering of the combo list items is important, because later their position index is assigned to the value of
   // CAbstractEmulatorOptions::E_Emulator enum
   m_ComboEmulator->addItem("GnuBoy"); // first item (0)
   m_ComboEmulator->addItem("VisualBoyAdvance"); // second item (1)
}


void CMainForm::connectObjects() {
   // register all events of the main widgets
   connect(m_ButtonEnde, SIGNAL(clicked()), this, SLOT(close()));
   connect(m_ButtonStart, SIGNAL(clicked()), this, SLOT(btnStartClicked()));
   connect(m_ButtonAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));
   connect(m_ButtonDel, SIGNAL(clicked()), this, SLOT(btnDelClicked()));
   connect(m_EmuProcess, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(gameStatusChanged(QProcess::ProcessState)));
   connect(m_ListViewGames->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this,
           SLOT(selectedGameChanged(const QItemSelection&, const QItemSelection&)));
   connect(m_ComboEmulator, SIGNAL(currentIndexChanged(int)), this, SLOT(emulatorChanged(int)));
}


void CMainForm::btnStartClicked() {
   // Start the currently selected game
   QStringList args;
   QItemSelectionModel *selectionModel = m_ListViewGames->selectionModel();

   if (selectionModel->selectedRows().count() == 1) {
      CGame game = m_GameList->getItem(selectionModel->selectedRows().first());

      if (game.getType() == CGame::INVALID) {
         QMessageBox::warning(this, trUtf8("Starting game"),
                              trUtf8("The file \"%1\" doesn't seem to be a valid GameBoy ROM file. The game cannot be started.")
                              .arg(game.getFilename()));
         return;
      }
      // TODO: Outsource compatibility test to game/options
      if (game.getType() == CGame::GAMEBOYADVANCE && game.getOptions().getEmulator() == CAbstractEmulatorOptions::GNUBOY) {
         QMessageBox::warning(this, trUtf8("Starting game"),trUtf8("\"%1\" is a GameBoy Advance game, but Gnuboy doesn't support Gameboy" \
            " Advance emulation. Please play this game using the VBA.").arg(game.getName()));
         return;
      }

      // Start the selected emulator with a command line according to all configured options
      args = game.getOptions().getCommandArgs();
      args += game.getFilename();

      // Print out the command line for debugging porposes
      qDebug() << "Starting emulator with command: " << game.getOptions().getEmuCommand();
      qDebug() << "and command line arguments: " << args;


      m_EmuProcess->start(game.getOptions().getEmuCommand(), args);
      if (m_EmuProcess->waitForStarted(-1) == false) {
         QMessageBox::warning(this, trUtf8("Starting game"), trUtf8("The game cannot be started because an error occured."));
      }
   }
   else {
      QMessageBox::warning(this, trUtf8("Starting game"), trUtf8("No game selected! Please choose the game to start from the game list!"));
   }
}


void CMainForm::btnAddClicked() {
   // Add a new game
   bool ok;
   QString gametitle;
   QString filename = QFileDialog::getOpenFileName(this, trUtf8("Choose ROM file"), QDir::homePath(), trUtf8("GameBoy ROM files")+" (*.gb *.gbc *.gba)");

   if (filename != "") { // Cancel the process when clicking "cancel" ;)
      CGame game(filename);
      gametitle = QInputDialog::getText(this, trUtf8("Enter game title"), trUtf8("Name of the game:"), QLineEdit::Normal, game.getIdentifier(), &ok);
      if (ok && !gametitle.isEmpty()) game.setName(gametitle);
      m_GameList->addItem(game);

      // resize the view columns and rows to fit all the contents
      m_ListViewGames->resizeColumnsToContents();
      m_ListViewGames->resizeRowsToContents();
   }
}


void CMainForm::btnDelClicked() {
   // Remove the currently selected game from the list
   QItemSelectionModel *selectionModel = m_ListViewGames->selectionModel();

   if (selectionModel->selectedRows().count() == 1) {
      m_GameList->removeRow(selectionModel->selectedRows().first().row(), selectionModel->selectedRows().first());
   }
   else {
      QMessageBox::warning(this, trUtf8("Remove game"), trUtf8("No game has been selected! Please select the game to remove from the list!")); // Es ist kein Spiel ausgewählt! Bitte wähle das zu löschende Spiel aus der Liste aus!
   }
}


void CMainForm::gameStatusChanged(QProcess::ProcessState newState) {
   // Will be called when a sub-process (the game emulator) started or ended
   switch (newState) {
   case QProcess::NotRunning:
      m_ButtonStart->setEnabled(true);
      break;
   case QProcess::Starting:
   case QProcess::Running:
      m_ButtonStart->setEnabled(false);
      break;
   }
}


void CMainForm::selectedGameChanged(const QItemSelection & selected, const QItemSelection & deselected) {
   // The user selected another game entry in the table list view
   if (selected.count() == 1) {
      m_FrameOptions->setEnabled(true);

      // A game was selected --> show the corresponding options widget on the right side
      CAbstractEmulatorOptions& gameOptions = m_GameList->getItem(selected.indexes().first()).getOptions();
      if (gameOptions.getEmulator() == CAbstractEmulatorOptions::GNUBOY) {
         m_ComboEmulator->blockSignals(true);
         m_ComboEmulator->setCurrentIndex(CAbstractEmulatorOptions::GNUBOY);
         m_ComboEmulator->blockSignals(false);
      }
      else {
         m_ComboEmulator->blockSignals(true);
         m_ComboEmulator->setCurrentIndex(CAbstractEmulatorOptions::VBA);
         m_ComboEmulator->blockSignals(false);
      }
      // Remove the old options widget from the layout and delete it, but only if it's there at all ;)
      if (m_OptionsWidget != 0) {
         m_OptionsVBox->removeWidget(m_OptionsWidget);
         delete m_OptionsWidget;
      }

      // Show the options widget that corresponds to the new loaded "options" object
      m_OptionsWidget = gameOptions.getOptionsWidget();
      m_OptionsVBox->addWidget(m_OptionsWidget);
   }
   else {
      m_FrameOptions->setEnabled(false);
   }
}


void CMainForm::emulatorChanged(int index) {
   // Another emulator was chosen for the current game --> Change the options widget (all formerly emulator options will be lost))
   CGame& currentGame = m_GameList->getItem(m_ListViewGames->selectionModel()->selectedRows().first());

   // remove the options widget from the layout and delete it, but only if it's there at all ;)
   if (m_OptionsWidget != 0) {
      m_OptionsVBox->removeWidget(m_OptionsWidget);
      delete m_OptionsWidget;
   }

   if (index == CAbstractEmulatorOptions::GNUBOY) {
      currentGame.changeEmulator(CAbstractEmulatorOptions::GNUBOY);
   }
   else {
      currentGame.changeEmulator(CAbstractEmulatorOptions::VBA);
   }

   // Show the options widget that corresponds to the new loaded "options" object
   m_OptionsWidget = currentGame.getOptions().getOptionsWidget();
   m_OptionsVBox->addWidget(m_OptionsWidget);
}



CMainForm::CMainForm(QWidget *parent)
        : QWidget(parent)
        , m_GameList(new CGameListModel())
        , m_OptionsWidget(0)
{
   // Define an application icon
   QIcon icon(":/img/gnuboy.png");
   qApp->setWindowIcon(icon);
   this->setWindowTitle("KBoy");

   // Load the game list
   CXmlGameListLoader loader(QDir::homePath() + "/.kboy/gamelist.xml");
   loader.readGameList(m_GameList); // The list will simply stay empty on read/parse error
   // TODO Exception handling for file reading...

   m_EmuProcess = new QProcess(this);

   // Build the GUI
   initWidgets();
   buildGUI();
   configureWidgets();

   // connect all signals and slots
   connectObjects();
}


CMainForm::~CMainForm() {
   // Save the game list to disk
   CXmlGameListWriter writer(QDir::homePath() + "/.kboy/gamelist.xml");
   try {
      writer.writeGameList(m_GameList);
   }
   catch (...) { // TODO: Correct exception handling...
   QMessageBox::critical(this, trUtf8("Unable to save file"), trUtf8("The game list cannot be written into file \"%1\"!").arg(QDir::homePath())); // Die m_GameList kann nicht gespeichert werden! Schreiben in Datei \"%1\" nicht möglich!
   }

   // remove the options widget from the layout and delete it, but only if it's there at all ;)
   if (m_OptionsWidget != 0) {
      m_OptionsVBox->removeWidget(m_OptionsWidget);
      delete m_OptionsWidget;
   }

   delete m_EmuProcess;
   delete m_GameList;
}


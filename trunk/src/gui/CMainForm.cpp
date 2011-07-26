   #include <QDebug>

#include "dao/xml/CXmlGameListLoader.hpp"
#include "dao/xml/CXmlGameListWriter.hpp"
#include "emulators/CAbstractEmulatorOptions.hpp"

#include "gui/CMainForm.hpp"

void CMainForm::initWidgets() {
    // Alle Widgets initialisieren
    // Layouts
    MainHBox = new QHBoxLayout();
    SpieleButtonHBox = new QHBoxLayout();
    SpieleFrameBox = new QVBoxLayout();
    RechtsVBox = new QVBoxLayout();
    OptionenVBox = new QVBoxLayout();

    // Container
    FrameListe = new QGroupBox(trUtf8("Rom-Files"));
    FrameOptionen = new QGroupBox(trUtf8("Emulator-Optionen"));
    SpieleFrameButtonBox = new QWidget();
    BoxRechts = new QWidget();
    //GnuboyOptionenBox=new CGnuboyOptionsWidget();
    //VBAOptionenBox=new CVBAOptionsWidget();


    // Steuerelemente
    ButtonAdd = new QPushButton(trUtf8("Hinzufügen"));
    ButtonDel = new QPushButton(trUtf8("Entfernen"));
    ButtonStart = new QPushButton(trUtf8("Spiel starten"));
    ButtonEnde = new QPushButton(trUtf8("Schließen"));
    ListViewSpiele = new QTableView();
    ComboEmulator = new QComboBox();
}


void CMainForm::buildGUI() {
    // Oberfläche zusammenbauen

    /* Linker Frame (Spieleliste) */
    // Buttonleiste
    SpieleButtonHBox->addWidget(ButtonAdd);
    SpieleButtonHBox->addWidget(ButtonDel);
    SpieleFrameButtonBox->setLayout(SpieleButtonHBox);
    // Spiele-Frame
    SpieleFrameBox->addWidget(ListViewSpiele);
    SpieleFrameBox->addWidget(SpieleFrameButtonBox);
    FrameListe->setLayout(SpieleFrameBox);

    /* Rechter Frame (Optionen & Buttons) */
    // Optionen-Feld
    OptionenVBox->addWidget(ComboEmulator);
    OptionenVBox->addSpacing(15);
    //OptionenVBox->addWidget(GnuboyOptionenBox);
    //OptionenVBox->addWidget(VBAOptionenBox);
    /* Ende Emulator-Optionen */

    FrameOptionen->setLayout(OptionenVBox);
    RechtsVBox->addWidget(FrameOptionen);
    RechtsVBox->addWidget(ButtonStart);
    RechtsVBox->addSpacing(10);
    RechtsVBox->addWidget(ButtonEnde);
    BoxRechts->setLayout(RechtsVBox);

    /* Haupt-Layout */
    MainHBox->addWidget(FrameListe);
    MainHBox->addWidget(BoxRechts);
    this->setLayout(MainHBox);
}


void CMainForm::configureWidgets() {
    // Widgets konfigurieren
    ListViewSpiele->setModel(Spieleliste);
    ListViewSpiele->verticalHeader()->hide();
    ListViewSpiele->setWordWrap(false);
    ListViewSpiele->resizeColumnsToContents();
    ListViewSpiele->resizeRowsToContents();
    ListViewSpiele->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ListViewSpiele->setSelectionMode(QAbstractItemView::SingleSelection);
    ListViewSpiele->setSelectionBehavior(QAbstractItemView::SelectRows);

    FrameOptionen->setEnabled(false);

    /*GnuboyOptionenBox->setVisible(false);
    VBAOptionenBox->setVisible(false);*/

    // Reihenfolge der Listeneinträge ist wichtig, weil darüber nachher die Zuordnung für die Auswahl läuft!
    ComboEmulator->addItem("GnuBoy"); // Erster Eintrag
    ComboEmulator->addItem("VisualBoyAdvance"); // Zweiter Eintrag
}


void CMainForm::connectObjects() {
    // Ereignishandler fuer Widget registrieren
    connect(ButtonEnde, SIGNAL(clicked()), this, SLOT(close()));
    connect(ButtonStart, SIGNAL(clicked()), this, SLOT(btnStartClicked()));
    connect(ButtonAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));
    connect(ButtonDel, SIGNAL(clicked()), this, SLOT(btnDelClicked()));
    connect(Gnuboy, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(gameStatusChanged(QProcess::ProcessState)));
    connect(ListViewSpiele->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(selectedGameChanged(const QItemSelection&, const QItemSelection&)));
    connect(ComboEmulator, SIGNAL(currentIndexChanged(int)), this, SLOT(emulatorChanged(int)));
}


void CMainForm::btnStartClicked() {
    QStringList Args;
    QItemSelectionModel *selectionModel = ListViewSpiele->selectionModel();

    if (selectionModel->selectedRows().count() == 1) {
        CGame Spiel = Spieleliste->getItem(selectionModel->selectedRows().first());

        if (Spiel.getType() == CGame::INVALID) {
            QMessageBox::warning(this, trUtf8("Spiel starten"), trUtf8("Die Datei \"%1\" scheint kein gültiges Gameboy-ROM zu sein. Das Spiel kann nicht gestartet werden.").arg(Spiel.getFilename()));
            return;
        }
        if (Spiel.getType() == CGame::GAMEBOYADVANCE && Spiel.getOptions().getEmulator() == CAbstractEmulatorOptions::GNUBOY) {
            QMessageBox::warning(this, trUtf8("Spiel starten"), trUtf8("\"%1\" ist ein Gamboy Advance-Spiel. GnuBoy unterstützt die Emulation des Gamboy Advance aber nicht, weshalb dieses Spiel mit dem VBA ausgeführt werden muss.").arg(Spiel.getName()));
            return;
        }

        // Emulator mit entsprechender Kommandozeile starten
        Args = Spiel.getOptions().getCommandArgs();
        Args += Spiel.getFilename();

        // Print out the command line for debugging porposes
        qDebug() << "Starting emulator with command: " << Spiel.getOptions().getEmuCommand();
        qDebug() << "and command line arguments: " << Args;


        Gnuboy->start(Spiel.getOptions().getEmuCommand(), Args);
        if (Gnuboy->waitForStarted(-1) == false) {
            QMessageBox::warning(this, trUtf8("Spiel starten"), trUtf8("Das Spiel konnte nicht gestartet werden. Es ist  ein Fehler aufgetreten."));
        }
    }
    else {
        QMessageBox::warning(this, trUtf8("Spiel starten"), trUtf8("Es ist kein Spiel ausgewählt! Bitte wähle das gewünschte Spiel aus der Liste aus!"));
    }
}


void CMainForm::btnAddClicked() {
    bool ok;
    QString Spielname;
    QString Filename = QFileDialog::getOpenFileName(this, trUtf8("ROM-Datei auswählen"), QDir::homePath(), trUtf8("GameBoy-ROMs (*.gb *.gbc *.gba)"));

    if (Filename != "") { // Mit OK verlassen
        CGame Spiel(Filename);
        Spielname = QInputDialog::getText(this, trUtf8("Spielname eingeben"), trUtf8("Name des Spiels:"), QLineEdit::Normal, Spiel.getIdentifier(), &ok);
        if (ok && !Spielname.isEmpty()) Spiel.setName(Spielname);
        Spieleliste->addItem(Spiel);

        ListViewSpiele->resizeColumnsToContents();
        ListViewSpiele->resizeRowsToContents();
    }
}


void CMainForm::btnDelClicked() {
    QItemSelectionModel *selectionModel = ListViewSpiele->selectionModel();

    if (selectionModel->selectedRows().count() == 1) {
        Spieleliste->removeRow(selectionModel->selectedRows().first().row(), selectionModel->selectedRows().first());
    }
    else {
        QMessageBox::warning(this, trUtf8("Spiel löschen"), trUtf8("Es ist kein Spiel ausgewählt! Bitte wähle das zu löschende Spiel aus der Liste aus!"));
    }
}


void CMainForm::gameStatusChanged(QProcess::ProcessState newState) {
    switch (newState) {
    case QProcess::NotRunning:
        ButtonStart->setEnabled(true);
        break;
    case QProcess::Starting:
    case QProcess::Running:
        ButtonStart->setEnabled(false);
        break;
    }
}


void CMainForm::selectedGameChanged(const QItemSelection & selected, const QItemSelection & deselected) {
    if (selected.count() == 1) {
        FrameOptionen->setEnabled(true);

        // Spiel ausgewählt --> Optionen rechts anzeigen
        CAbstractEmulatorOptions& gameOptions = Spieleliste->getItem(selected.indexes().first()).getOptions();
        if (gameOptions.getEmulator() == CAbstractEmulatorOptions::GNUBOY) {
            ComboEmulator->blockSignals(true);
            ComboEmulator->setCurrentIndex(CAbstractEmulatorOptions::GNUBOY);
            ComboEmulator->blockSignals(false);
            /*GnuboyOptionenBox->setOptionsPtr(((CGnuboyOptions*)Spieleliste->getItem(selected.indexes().first()).getOptions()));
            VBAOptionenBox->setVisible(false);
            GnuboyOptionenBox->setVisible(true);*/
        }
        else {
            ComboEmulator->blockSignals(true);
            ComboEmulator->setCurrentIndex(CAbstractEmulatorOptions::VBA);
            ComboEmulator->blockSignals(false);
            /*VBAOptionenBox->setOptionsPtr(((CVBAOptions*)Spieleliste->getItem(selected.indexes().first()).getOptions()));
            GnuboyOptionenBox->setVisible(false);
            VBAOptionenBox->setVisible(true);*/
        }
        // remove the options widget from the layout and delete it, but only if it's there at all ;)
        if (OptionsWidget != 0) {
            OptionenVBox->removeWidget(OptionsWidget);
            delete OptionsWidget;
        }

        // Show the options widget that corresponds to the new loaded "options" object
        OptionsWidget = gameOptions.getOptionsWidget();
        OptionenVBox->addWidget(OptionsWidget);
    }
    else {
        FrameOptionen->setEnabled(false);
    }
}


void CMainForm::emulatorChanged(int index) {
    // Emulator geändert --> Widgets austauschen
    CGame& Spiel = Spieleliste->getItem(ListViewSpiele->selectionModel()->selectedRows().first());

    // remove the options widget from the layout and delete it, but only if it's there at all ;)
    if (OptionsWidget != 0) {
        OptionenVBox->removeWidget(OptionsWidget);
        delete OptionsWidget;
    }

    if (index == CAbstractEmulatorOptions::GNUBOY) {
        Spiel.changeEmulator(CAbstractEmulatorOptions::GNUBOY);
    }
    else {
        Spiel.changeEmulator(CAbstractEmulatorOptions::VBA);
    }

    // Show the options widget that corresponds to the new loaded "options" object
    OptionsWidget = Spiel.getOptions().getOptionsWidget();
    OptionenVBox->addWidget(OptionsWidget);
}


CMainForm::CMainForm(QWidget *parent)
        : QWidget(parent)
        , OptionsWidget(0) {
    // Icon für die Anwendung festlegen
    QIcon Icon(":/img/gnuboy.png");
    qApp->setWindowIcon(Icon);
    this->setWindowTitle(trUtf8("KBoy"));

    // Objektmember initialisieren
    CXmlGameListLoader loader(QDir::homePath() + "/.kboy/gamelist.xml");
    Spieleliste = new CGameListModel();
    loader.readGameList(Spieleliste); // Wenn Datei nicht geladen werden kann, bleibt die Liste leer
    // TODO Exception handling...
    Gnuboy = new QProcess(this);

    // Grafische Oberfläche aufbauen
    initWidgets();
    buildGUI();
    configureWidgets();

    // Signal-/Slot-Objekte verknüpfen
    connectObjects();
}


CMainForm::~CMainForm() {
    // Spieleliste speichern
    CXmlGameListWriter writer(QDir::homePath() + "/.kboy/gamelist.xml");
    try {
        writer.writeGameList(Spieleliste);
    }
    catch (...) { // TODO: Correct exception handling...
        QMessageBox::critical(this, trUtf8("Datei speichern nicht möglich"), trUtf8("Die Spieleliste kann nicht gespeichert werden! Schreiben in Datei \"%1\" nicht möglich!").arg(QDir::homePath()));
    }
    // TODO EmuOptionen löschen!
    // remove the options widget from the layout and delete it, but only if it's there at all ;)
    if (OptionsWidget != 0) {
        OptionenVBox->removeWidget(OptionsWidget);
        delete OptionsWidget;
    }

    delete Gnuboy;
    //delete Spieleliste;
}


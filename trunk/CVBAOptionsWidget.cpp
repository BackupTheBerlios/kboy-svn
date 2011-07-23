#include "CVBAOptionsWidget.h"

CVBAOptionsWidget::CVBAOptionsWidget(QWidget *parent):CAbstraktOptionsWidget(parent) {
	prOptions=0; // Mit 0 initialisieren, wird erst später gesetzt!
	
	// GUI-Elemente initialisieren
	
	// GUI zusammenbauen
	// "Haupt"-Feld
	OptionenVBox->addWidget(CheckFullscreen);
	OptionenVBox->addWidget(ScaleBox);
	
	// Events verknüpfen
	connect(CheckFullscreen, SIGNAL(stateChanged(int)), this, SLOT(FullscreenChanged(int)));
	connect(SpinScale, SIGNAL(valueChanged(int)), this, SLOT(ScaleChanged(int)));
	connect(EditCmdLine, SIGNAL(textEdited(const QString&)), this, SLOT(CmdlineChanged(const QString&)));
}



void CVBAOptionsWidget::FullscreenChanged(int State) {
	if(prOptions!=0) prOptions->setFullscreen(State==Qt::Checked?true:false);
}



void CVBAOptionsWidget::ScaleChanged(int Scale) {
	if(prOptions!=0) prOptions->setScale(Scale);
}

void CVBAOptionsWidget::CmdlineChanged(const QString& text) {
	if(prOptions!=0) prOptions->setEmuCommand(text);
}


void CVBAOptionsWidget::setOptionsPtr(CVBAOptions *Options) {
	prOptions=Options;
	// Alle Steuerelemente den neuen Optionen anpassen
	CheckFullscreen->setCheckState(prOptions->getFullscreen()==true?Qt::Checked:Qt::Unchecked);
	SpinScale->setValue(prOptions->getScale());
	EditCmdLine->setText(prOptions->getEmuCommand());
}

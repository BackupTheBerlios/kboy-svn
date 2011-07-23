#include "CGnuboyOptionsWidget.h"

CGnuboyOptionsWidget::CGnuboyOptionsWidget(QWidget *parent):CAbstraktOptionsWidget(parent) {
	prOptions=0; // Mit 0 initialisieren, wird erst später gesetzt!
	
	// GUI-Elemente initialisieren
	CheckHardwareAccl=new QCheckBox(trUtf8("Hardwarebeschleunigung"));
	CheckSound=new QCheckBox(trUtf8("Sound"));
	
	// GUI zusammenbauen
	// "Haupt"-Feld
	OptionenVBox->addWidget(CheckFullscreen);
	OptionenVBox->addWidget(CheckHardwareAccl);
	OptionenVBox->addWidget(ScaleBox);
	OptionenVBox->addSpacing(15);
	OptionenVBox->addWidget(CheckSound);
	
	// GUI-Elemente konfigurieren
	
	
	// Events verknüpfen
	connect(CheckFullscreen, SIGNAL(stateChanged(int)), this, SLOT(FullscreenChanged(int)));
	connect(CheckSound, SIGNAL(stateChanged(int)), this, SLOT(SoundChanged(int)));
	connect(CheckHardwareAccl, SIGNAL(stateChanged(int)), this, SLOT(HardwareAcclChanged(int)));
	connect(SpinScale, SIGNAL(valueChanged(int)), this, SLOT(ScaleChanged(int)));
	connect(EditCmdLine, SIGNAL(textEdited(const QString&)), this, SLOT(CmdlineChanged(const QString&)));
}



void CGnuboyOptionsWidget::FullscreenChanged(int State) {
	if(prOptions!=0) prOptions->setFullscreen(State==Qt::Checked?true:false);
}


void CGnuboyOptionsWidget::SoundChanged(int State) {
	if(prOptions!=0) prOptions->setSound(State==Qt::Checked?true:false);
}


void CGnuboyOptionsWidget::HardwareAcclChanged(int State) {
	if(prOptions!=0) prOptions->setHardwareAccl(State==Qt::Checked?true:false);
}


void CGnuboyOptionsWidget::ScaleChanged(int Scale) {
	if(prOptions!=0) prOptions->setScale(Scale);
}


void CGnuboyOptionsWidget::CmdlineChanged(const QString& text) {
	if(prOptions!=0) prOptions->setEmuCommand(text);
}


void CGnuboyOptionsWidget::setOptionsPtr(CGnuboyOptions *Options) {
	prOptions=Options;
	// Alle Steuerelemente den neuen Optionen anpassen
	CheckFullscreen->setCheckState(prOptions->getFullscreen()==true?Qt::Checked:Qt::Unchecked);
	CheckSound->setCheckState(prOptions->getSound()==true?Qt::Checked:Qt::Unchecked);
	CheckHardwareAccl->setCheckState(prOptions->getHardwareAccl()==true?Qt::Checked:Qt::Unchecked);
	SpinScale->setValue(prOptions->getScale());
	EditCmdLine->setText(prOptions->getEmuCommand());
}

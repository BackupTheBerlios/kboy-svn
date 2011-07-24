#if 0
  
#include "CAbstraktOptionsWidget.h"

CAbstraktOptionsWidget::CAbstraktOptionsWidget(QWidget *parent):QWidget(parent) {
	// GUI-Elemente initialisieren
	OptionenVBox=new QVBoxLayout();
	ScaleBox=new QWidget();
	ScaleHBox=new QFormLayout();
	CheckFullscreen=new QCheckBox(trUtf8("Vollbildmodus"));
	SpinScale=new QSpinBox();
	CmdLineHBox=new QFormLayout();
	CmdLineBox=new QWidget();
	EditCmdLine=new QLineEdit();
	
	// GUI zusammenbauen
	// Scale-Feld
	ScaleHBox->addRow(trUtf8("Vergrößerung"), SpinScale);
	ScaleBox->setLayout(ScaleHBox);
	// Kommandozeilen-Feld
	CmdLineHBox->addRow(trUtf8("Kommandozeile:"), EditCmdLine);
	CmdLineBox->setLayout(CmdLineHBox);
	
	OptionenVBox->addWidget(CmdLineBox);
	OptionenVBox->addSpacing(10);
	this->setLayout(OptionenVBox);
	
	// GUI-Elemente konfigurieren
	SpinScale->setRange(1,4);
	SpinScale->setSingleStep(1);

}

#endif

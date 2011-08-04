#include "emulators/gnuboy/CGnuboyOptionsWidget.hpp"


CGnuboyOptionsWidget::CGnuboyOptionsWidget(CGnuboyOptions& emulatorOptions, QWidget *parent)
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
   CheckHardwareAccl = new QCheckBox(trUtf8("hardware acceleration"));
   CheckSound = new QCheckBox(trUtf8("sound"));

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
   OptionenVBox->addWidget(CheckHardwareAccl);
   OptionenVBox->addWidget(ScaleBox);
   OptionenVBox->addSpacing(15);
   OptionenVBox->addWidget(CheckSound);

   this->setLayout(OptionenVBox);

   // configure all GUI elements
   SpinScale->setRange(1, 4);
   SpinScale->setSingleStep(1);

   // set all GUI elements to the current option values
   CheckFullscreen->setCheckState(m_Options.getFullscreen() == true ? Qt::Checked : Qt::Unchecked);
   CheckSound->setCheckState(m_Options.getSound() == true ? Qt::Checked : Qt::Unchecked);
   CheckHardwareAccl->setCheckState(m_Options.getHardwareAccl() == true ? Qt::Checked : Qt::Unchecked);
   SpinScale->setValue(m_Options.getScale());
   EditCmdLine->setText(m_Options.getEmuCommand());

   // connect all events
   connect(CheckFullscreen, SIGNAL(stateChanged(int)), this, SLOT(fullscreenChanged(int)));
   connect(CheckSound, SIGNAL(stateChanged(int)), this, SLOT(soundChanged(int)));
   connect(CheckHardwareAccl, SIGNAL(stateChanged(int)), this, SLOT(hardwareAcclChanged(int)));
   connect(SpinScale, SIGNAL(valueChanged(int)), this, SLOT(scaleChanged(int)));
   connect(EditCmdLine, SIGNAL(textEdited(const QString&)), this, SLOT(cmdlineChanged(const QString&)));
}


void CGnuboyOptionsWidget::fullscreenChanged(int state) {
   m_Options.setFullscreen(state == Qt::Checked ? true : false);
}


void CGnuboyOptionsWidget::soundChanged(int state) {
   m_Options.setHardwareAccl(state == Qt::Checked ? true : false);
}


void CGnuboyOptionsWidget::hardwareAcclChanged(int state) {
   m_Options.setHardwareAccl(state == Qt::Checked ? true : false);
}


void CGnuboyOptionsWidget::scaleChanged(int scale) {
   m_Options.setScale(scale);
}


void CGnuboyOptionsWidget::cmdlineChanged(const QString& text) {
   m_Options.setEmuCommand(text);
}




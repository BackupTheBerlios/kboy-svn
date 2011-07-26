
#include "emulators/vba/CVBAOptionsWidget.hpp"


CVBAOptionsWidget::CVBAOptionsWidget(CVBAOptions& emulatorOptions, QWidget *parent)
      : QWidget(parent)
      , m_Options(emulatorOptions)
{
   // Initialize all GUI elements
   OptionenVBox = new QVBoxLayout();
   ScaleBox = new QWidget();
   ScaleHBox = new QFormLayout();
   CheckFullscreen = new QCheckBox(trUtf8("Vollbildmodus"));
   SpinScale = new QSpinBox();
   CmdLineHBox = new QFormLayout();
   CmdLineBox = new QWidget();
   EditCmdLine = new QLineEdit();

   // create all GUI elements
   // "graphics scale" input
   ScaleHBox->addRow(trUtf8("Vergrößerung"), SpinScale);
   ScaleBox->setLayout(ScaleHBox);
   // "command line" input
   CmdLineHBox->addRow(trUtf8("Kommandozeile:"), EditCmdLine);
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



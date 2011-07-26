#include "emulators/CAbstractEmulatorOptions.hpp"

// The following two includes are needed for the "factory method" that creates new option objects
#include "emulators/gnuboy/CGnuboyOptions.hpp"
#include "emulators/vba/CVBAOptions.hpp"


CAbstractEmulatorOptions::CAbstractEmulatorOptions() {
   // Use gnuboy as standard
   setEmulator(GNUBOY);
}

enum CAbstractEmulatorOptions::E_Emulator CAbstractEmulatorOptions::getEmulator() const {
   return m_Emulator;
}

void CAbstractEmulatorOptions::setEmulator(enum CAbstractEmulatorOptions::E_Emulator emulator) {
   m_Emulator = emulator;
}



std::auto_ptr<CAbstractEmulatorOptions> CAbstractEmulatorOptions::createEmulatorOptions(CAbstractEmulatorOptions::E_Emulator emulator) {
   switch(emulator) {
      case GNUBOY:
         return std::auto_ptr<CAbstractEmulatorOptions>(new CGnuboyOptions());
         break;
      case VBA:
         return std::auto_ptr<CAbstractEmulatorOptions>(new CVBAOptions());
         break;
         // TODO: Error output on "default"?
   }
}

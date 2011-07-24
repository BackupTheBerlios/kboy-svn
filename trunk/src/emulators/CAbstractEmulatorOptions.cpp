#include "emulators/CAbstractEmulatorOptions.hpp"

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

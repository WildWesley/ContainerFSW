#include "Common.h"
#include "Hardware.h"
#include "States.h"

namespace States
{
  void Landing()
  {
    // Polling is stopped
    // Poll_Payload.stop()
    EEPROM.put(Common::ST_ADDR, 0);

    // Container stops its telemetry
    // Poll_Sensors.stop()

    // Sound Beacon
    Hardware::buzzer_on();

    // Container stops recording
    Hardware::update_camera(false);
  }
}

#include <SSR.h>

SSR heater;

uint32_t lastRun;
uint8_t pwr = 0;

void setup() {
  heater.setup(LED_BUILTIN, SSR::MODE_PULSE_PACKET);
  Serial.begin(115200);
  Serial.println("Start");
  lastRun = millis();
}

void loop() {
  uint32_t now;
  uint8_t state;
  

  now = millis();
  if ((now-lastRun) >= 3*1000){
    // proceed with next setting after 3 secs
    lastRun = now;
    
    if ((pwr += 10) > 100) pwr = 0;
    Serial.println(pwr, DEC);
    heater.setPower(pwr);
    
  }

  heater.run();
/*
  while (Serial.available()){
    Serial.read();
    state = ++state & 1;
    Serial.print("\nState = ");Serial.println(state, DEC);
    
    heater.setPower(state);
  }
*/
}

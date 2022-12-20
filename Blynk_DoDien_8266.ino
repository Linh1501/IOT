
//-----------------Pzem---------------
#include "Pzem004t_V3.h"
Pzem004t_V3 pzem(&Serial);


//-----------------Blynk---------------
#define BLYNK_TEMPLATE_ID "TMPL027zFg4r"
#define BLYNK_DEVICE_NAME "QuanLyDien"

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG


#include "BlynkEdgent.h"

void setup()
{
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
  pzem.begin();
}

BLYNK_WRITE(V6) {  // Button Widget chọn V0
  if (param.asInt() == 1) {  //nếu nhấn nút reset thì gọi hàm
    pzem.resetEnergy(); // reset PZEM
  } else {  

  }}

void SendToBlynk()
{
  pzem_info pzemData = pzem.getData();
  Blynk.virtualWrite(V0, pzemData.volt);
  Blynk.virtualWrite(V1, pzemData.ampe);
  Blynk.virtualWrite(V2, pzemData.power);
  Blynk.virtualWrite(V3, pzemData.energy);
  Blynk.virtualWrite(V4, pzemData.powerFactor); // cosphi
  Blynk.virtualWrite(V5, pzemData.freq);
 
}


void loop() {
  SendToBlynk();
  BlynkEdgent.run();
}

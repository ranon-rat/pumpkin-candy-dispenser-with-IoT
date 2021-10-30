#include <Arduino.h>
#include "esp_camera.h"
#include "esp_timer.h"

// idk wtf this does
#include "fb_gfx.h"
#include "soc/soc.h"          //disable brownout problems
#include "soc/rtc_cntl_reg.h" //disable brownout problems


#define CAMERA_MODEL_AI_THINKER
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WITHOUT_PSRAM
//#define CAMERA_MODEL_WROVER_KIT
#include "camera-config.h"
#include "service.hpp"

#include "network-config.h"

void setup()
{
  

  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector

  Serial.begin(115200);
  Serial.setDebugOutput(false);
  camera_config_t config = setup_camera_config(); // get the camera config
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK)
  {
    Serial.printf("Camera init failed with error 0x%x", err); // in case of error
    return;
  }
  WiFi.begin((char *)SSID, (char *)PASS); // connect to our own network
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.printf("\nWiFi connected\n\nCamera Stream Ready! Go to: http://%s\n", WiFi.localIP().toString().c_str());
  startServer();
}

void loop()
{
  
  // put your main code here, to run repeatedly:
}
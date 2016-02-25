#include <Wire.h>
#include <rgb_lcd.h>

#include "LGATTSUart.h"
#include "LGATTSABC.h"
#include <LGATTUUID.h>

#ifdef APP_LOG
#undef APP_LOG
#endif

#define APP_LOG(...) Serial.printf(__VA_ARGS__); \
    Serial.println();

LGATTSUart uart;
LGATTUT abc;
rgb_lcd lcd;

int n=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("[LGATTS ino]Start.");
  //lcd.begin(16,2);
  lcd.clear();
  lcd.print("Waitting to Start.");
  
  for(int i=8;i>=0;i--){
    lcd.setCursor(15,0);
    lcd.print(i);
    delay(1000);
  }
  lcd.clear();
  
  //LGATTServer.begin(g_gatts_uuid, 1, &uart);
  
    if (!LGATTServer.begin(2, &uart, &abc))
    {
        APP_LOG("[LGATTS ino][FAILED] GATTS begin");
    }
    else
    {
        APP_LOG("[LGATTS ino]GATTS begin");
        lcd.print("GATTS begin");
        delay(700);
    }
    
    
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  LGATTServer.handleEvents();
  //LGATTAttributeValue value = {13, "hello, world!"};
  if (uart.isConnected())
  {
    LGATTAttributeValue value = {0};
    const char *str = "[peripheral] From Service to Client.";
    value.len = strlen(str);
    memcpy(value.value, str, value.len);
    boolean ret = uart.sendIndication(value, uart.getHandleNotify(), false);
    if (!ret)
    {
        APP_LOG("[LGATTS ino] [FAILED] send [%d]", ret);
    }
    //APP_LOG("[LGATTS ino] send [%d][%s]", ret, str);
  }
  //uart.send(value, uart.getHandle(0), false); // just a notify

}


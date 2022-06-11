#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin("Galaxy M32 5GFEE4", "Pavanraj@#123");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("..");
    delay(200);
  }
  Serial.println();
  Serial.println("NodeMCU is Connected!");
  Serial.println(WiFi.localIP());
  while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
} 
}

void loop() {
  String str;
  if (Serial.available()) {
    str = Serial.readStringUntil('\n');
  }
  HTTPClient http;
  WiFiClient wc;
  http.begin(wc,"http://waterqualitydetection.herokuapp.com/post");
  http.addHeader("Content-Type", "text/plain"); 
  int httpCode = http.POST(str);
  http.end();
  Serial.print("Uploaded");
  Serial.print(str);
  delay(5000);
}

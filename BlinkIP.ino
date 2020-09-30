#define HOST_NAME "BLINK_IP"
#define WIFI_SSID          "GW-FM-7390"
#define WIFI_PASS          "3tr67333"
#define SERIAL_SPEED 9600
#define STDLED     D4   // GPIO02 (& Console2 TX)
#include <ESP8266WiFi.h>
static IPAddress ip;
int wifiConnectCounter;
#define wifiMaxTries         30
#define wifiRepeatInterval   100

void blinkByte(byte value, byte pin)
{
  byte part;
  byte i;
  //Serial.println("Mark ");
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delay(2000);
  digitalWrite(pin, HIGH);
  delay (1000);
  //Serial.print("Blinking value: ");  Serial.println(value);

  part = value / 100 % 10;
  //Serial.print(part); Serial.print(" : ");
  for (i = 0; i < part; i++) {
    digitalWrite(pin, LOW);
    delay(100);
    digitalWrite(pin, HIGH);
    delay(500);
  }
  delay (1000);

  part = value / 10 % 10;
  //Serial.print(part); Serial.print(" : ");
  for (i = 0; i < part; i++) {
    digitalWrite(pin, LOW);
    delay(100);
    digitalWrite(pin, HIGH);
    delay(500);
  }
  delay(1000);

  part = value % 10;
  //Serial.println(part);
  for (i = 0; i < part; i++) {
    digitalWrite(pin, LOW);
    delay(100);
    digitalWrite(pin, HIGH);
    delay(500);
  }
  delay(2000);
}

void getWiFi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  wifi_station_set_auto_connect(true);
  wifi_station_set_hostname(HOST_NAME);
  wifiConnectCounter = 1;
  Serial.println();
  while (WiFi.status() != WL_CONNECTED) {
    delay(wifiRepeatInterval);
    Serial.print(".");
    wifiConnectCounter++;
    if (wifiConnectCounter > wifiMaxTries) {
      delay(wifiRepeatInterval * 1000 * 1000);
      wifiConnectCounter = 0;
    }
  }
  ip = WiFi.localIP();
}


void setup() {
  // put your setup code here, to run once:
  // Serial initialisation
  Serial.begin (SERIAL_SPEED); // On USB port
  Serial.println();

  getWiFi();
  //blinkByte(ip[2], STDLED);   Remove comment, if you want to get two last bytes blinked.
  blinkByte(ip[3], STDLED);

}


void loop() {
  // put your main code here, to run repeatedly:
}

#include <WiFiManager.h> // De library die je net hebt geïnstalleerd

void setup() {
  Serial.begin(115200);

  // WiFiManager object
  WiFiManager wm;

  // Optioneel: wist oude instellingen om opnieuw te beginnen (handig tijdens testen)
  // wm.resetSettings();

  // Dit is de magie: de ESP32 probeert te verbinden of opent de config-pagina
  // Als je hem voor het eerst aanzet, heet het wifi-netwerk "AutoConnectAP"
  if (!wm.autoConnect("ESP32_Config_Portal")) {
    Serial.println("Verbinding mislukt, opnieuw opstarten...");
    ESP.restart();
  }

  Serial.println("Verbonden met het internet! Je kunt nu je server aanroepen.");
}

void loop() {
  // Hier blijft je logica om data op te halen exact hetzelfde!
  // Je hoeft niets aan te passen aan de HTTP-aanroep.
}
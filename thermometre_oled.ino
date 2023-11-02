#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>

// Variables pour le débogage
unsigned long dernierTempsDebogage = 0; // Dernier moment où le débogage a été effectué
unsigned long intervalleDebogage = 3000;  // Intervalle de débogage en millisecondes (3 secondes)

#define BROCHE_DHT 2
#define TYPE_DHT DHT11
DHT dht(BROCHE_DHT, TYPE_DHT);

#define LARGEUR_ECRAN 128
#define HAUTEUR_ECRAN 64
#define OLED_RESET -1
Adafruit_SSD1306 display(LARGEUR_ECRAN, HAUTEUR_ECRAN, &Wire, OLED_RESET, 0x3C);  // Utilisation de l'adresse I2C 0x3C

void setup() {
  dht.begin();
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Utilisation de l'adresse I2C 0x3C
    Serial.println(F("Échec de l'initialisation SSD1306"));
    for (;;)
      ;
  }
}

void mettreAJourOLED(float temp, float hum) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Temperature : ");
  display.setCursor(0, 16);
  display.println("Humidite : ");
  display.setCursor(80, 0);
  display.print(int(temp));
  display.print("oC");
  display.setCursor(80, 16);
  display.print(int(hum));
  display.println("%");
  display.display();  // Actualiser l'affichage après avoir dessiné les valeurs
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  mettreAJourOLED(temp, hum);

  unsigned long tempsCourant = millis();
  if (tempsCourant - dernierTempsDebogage >= intervalleDebogage) {
    Serial.print("Humidité : ");
    Serial.print(hum);
    Serial.println("%");
    Serial.print("Température : ");
    Serial.print(temp);
    Serial.println("°C");
    Serial.println("-----------------------------");
    dernierTempsDebogage = tempsCourant;
  }
}

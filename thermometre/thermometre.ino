//Bibliotheque
#include "DHT.h"
#include <LiquidCrystal.h>

// Variables pour le débogage
unsigned long lastDebugTime = 0;     // Dernier moment où le débogage a été effectué
unsigned long debugInterval = 3000;  // Intervalle de débogage en millisecondes (3 secondes)


DHT dht(2, DHT11);                       //definition de la broche du capteur
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);  // definition des broche du lcd

void setup() {
  dht.begin();         //initialisation le capteur
  Serial.begin(9600);  // Débit de communication pour la communication série a 9600 bauds.
  lcd.begin(16, 2);    // définit le type d'écran lcd 16 x 2
}
void loop() {
  float hum = dht.readHumidity();      //lecture de l'humidité
  float temp = dht.readTemperature();  // lecture de la temperature

  if ((temp >= 19) && (temp < 21)) {  //teste si la temperature

    digitalWrite(5, HIGH);  // Led verte allumée
    digitalWrite(6, LOW);   //  Led rouge éteinte
  } else {
    digitalWrite(6, HIGH);  // Led rouge allumée
    digitalWrite(5, LOW);   // Led verte éteinte
  }

  // LCD
  lcd.setCursor(0, 0);
  lcd.print("Temperature: " + String(int(temp)) + ('\xDF'));
  lcd.setCursor(0, 1);
  lcd.print("Humidite: " + String(int(hum)) + ("%"));

  // Débogage
  unsigned long currentTime = millis();
  if (currentTime - lastDebugTime >= debugInterval) {
    // Effectuez le débogage toutes les 3 secondes
    Serial.print("Humidité: ");
    Serial.print(hum);
    Serial.println("%");
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println("°");
    Serial.println("-----------------------------");
    lastDebugTime = currentTime;  // Met à jour le dernier moment du débogage
  }
}

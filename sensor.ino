#include <DHT.h>

#define DHTPIN 4  
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println("DHTxx test!");
  dht.begin();
}

void loop() {
  // Espera 5 segundos antes de tomar otra lectura
  delay(5000);
  
  // Lee la temperatura y la humedad del sensor
  float hume = dht.readHumidity();
  float hume2 = (hume / 100); 
  float temp = dht.readTemperature();
  float temp2 = (temp / 5);

  // Verifica si la lectura del sensor fue exitosa
  if (isnan(temp2) || isnan(hume2)) {
    Serial.println("Error al leer el sensor DHT11");
    return;
  }
  
  // Imprime la temperatura y la humedad en el monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temp2);
  Serial.print(" °C\t");
  Serial.print("Humedad: ");
  Serial.print(hume2);
  Serial.println("%");
}


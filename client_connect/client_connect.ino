#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>

#include <WiFiClient.h>

const char* ssid = "Proyectos"; //Nombre de Red
const char* password = "Proyectos@2024"; //Clave de Red

float temperature;
float humidity;
float humidity2;
float temperature2; 


#include <DHT.h>
// Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

#define DHTPIN 4

#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

void setup() 
{
  Serial.begin(115200);
  Serial.println(F("DHT 22 prueba de conexión con el servidor"));
  dht.begin();
  WiFi.begin(ssid, password);
  Serial.print("Conectando...");
  while (WiFi.status()!= WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conexión OK!");
  Serial.print("IP Local: ");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  LecturaTH();
  EnvioDatos();
}

void LecturaTH()
{
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  humidity2 = (humidity / 100); 
  temperature2 = (temperature / 5);

  if (isnan(humidity2) || isnan(temperature2)) 
  {
    Serial.println(F("Failed to read from DHT sensor"));
    return;
  }
  else
  {
      Serial.print("Temperatura: ");
  Serial.print(temperature2);
  Serial.print("°C");
  Serial.print("Humedad: ");
  Serial.print(humidity2);
  Serial.println("%");
  }

}

void EnvioDatos()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    if (!isnan(temperature2) && !isnan(humidity2)) // Verifica si los valores son válidos
    {
      HTTPClient http; 
      String datos_a_enviar = "temperature=" + String(temperature2) + "&humidity=" + String(humidity2);
      http.begin(client, "https://mae2.000webhostapp.com/dht.php");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int codigo_respuesta = http.POST(datos_a_enviar);

      
      if (codigo_respuesta > 0)
      {
        Serial.println("Código HTTP: " + String(codigo_respuesta));
        if (codigo_respuesta == 200)
        {
          String cuerpo_respuesta = http.getString();
          Serial.println("El servidor respondió: ");
          Serial.println(cuerpo_respuesta);
        }
      } 
      else 
      {
        Serial.print("Error enviado POST, código: ");
        Serial.println(codigo_respuesta);
      }
      
      http.end(); 
    }
    else
    {
      Serial.println("Valores de temperatura o humedad no válidos. No se enviarán a la base de datos.");
    }
  } 
  else 
  {
    Serial.println("Error en la conexion WIFI");
  }
  delay(5000); // Espera 5 segundos
}

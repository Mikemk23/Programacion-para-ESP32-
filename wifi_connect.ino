#include <ESP8266WiFi.h>

const char* ssid = "Proyectos"; //Nombre de Red
const char* password = "Proyectos@2024"; //Clave de Red

byte cont = 0;
byte max_intentos = 50;

void setup() 
{
  Serial.begin(115200);
  Serial.println("\n");
  // Conexión a la red WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and cont < max_intentos) 
  {
    cont++;
    delay(500);
    Serial.print(".");
  }

Serial.println("");

if (cont < max_intentos) 
{
  Serial.println();
  Serial.print("Conectando a");
  Serial.println(ssid);
  
  Serial.println("");
  Serial.println("Conexión WiFi establecida");
  Serial.print("Dirección IP asignada: ");
  Serial.println(WiFi.localIP());
}

}
void loop() {

}
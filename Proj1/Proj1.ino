#include <Ethernet.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>                
#include <DallasTemperature.h>

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3F,16,2);  
OneWire puertosensor1(9);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensor1(&puertosensor1); //Se declara una variable u objeto para nuestro sensor
EthernetClient ethClient;

// Update these with values suitable for your network.
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,8,30);

long ahora,ultimamesura; //variables de tiempo
float temp1; //variables temperatura
const byte LED_SensorInductiu = 8;
bool StatSensorInductiu;

void setup() {
  pinMode(LED_SensorInductiu, INPUT);
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("HOLA MUNDO. Version 1-1");

  // Inicializar el LCD
  lcd.init();
  //Encender la luz de fondo.
  lcd.backlight();
  // Escribimos el Mensaje en el LCD.
  lcd.print("HOLA MUNDO");

  sensor1.begin();   //Se inicia el sensor 1

  Ethernet.begin(mac, ip);
  // Allow the hardware to sort itself out
  delay(1500);

}

void loop() {
  // put your main code here, to run repeatedly:
  ahora=millis();
  if ((ahora-ultimamesura)>3000) {
    ultimamesura = ahora;
    sensor1.requestTemperatures();   //Se envía el comando para leer la temperatura
    temp1= sensor1.getTempCByIndex(0); //Se obtiene la temperatura en ºC  
    // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
    lcd.setCursor(0, 1);
    lcd.print(temp1);
    lcd.print(" ");
    lcd.print("Cels");
    Serial.println(temp1);
  }
  // read the state of the pushbutton value:
  StatSensorInductiu = digitalRead(LED_SensorInductiu);
  //if(!StatSensorInductiu)
  
}

#include <ArduinoJson.h>
#include <SPI.h>
#include <TM1637Display.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Ethernet.h>

#define LED_RED 8
#define LED_GREEN 7
#define LED_YELLOW 6
#define CLK 2
#define DIO 3
#define DHTTYPE DHT11
#define DHTPIN A1

TM1637Display display = TM1637Display(CLK, DIO);
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
IPAddress serverIp(192, 168, 0, 177); // ip do servidor

uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G, // Circle
  SEG_A | SEG_D | SEG_E | SEG_F  // C
};
int serverPort = 3000;
EthernetClient client;
float temperatura;
float umidade;

void setup()
{  
  initialize();
  initializeEthernet();
}

void loop()
{
  
  Serial.println("loop..");
  readTemp();
  sendTemp(temperatura, umidade);
}

// *********************************************

void initialize()
{
  Serial.begin(9600);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  dht.begin();

  // SET 4-DIGITS DISPLAY
  display.setBrightness(1);
  display.setSegments(data);

  // INIT BLACKLIGHT
  lcd.init();
  lcd.setBacklight(HIGH);
}

void initializeEthernet()
{
  byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02}; // mac da shield ethernet
  byte ip[] = {192, 168, 0, 34};                     // ip do shield

  alerts("Conectando de ", "192.168.0.34");
  delay(1000);

  Ethernet.begin(mac, ip);
  if (Ethernet.hardwareStatus() == EthernetNoHardware)
  {
    alerts("ERROR", "COD 02"); // Placa ethernet não foi encontrada.
    while (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
      delay(100);
    }
  }

  if (Ethernet.linkStatus() == LinkOFF)
  {
    alerts("ERROR", "COD 03"); // LINK DESLIGADO
    while (Ethernet.linkStatus() == LinkOFF)
    {
      delay(100);
    }
  }
  client.connect(serverIp, serverPort);
  if (!client.connect(serverIp, serverPort))
  {
    while (!client.connect(serverIp, serverPort))
    { // enquanto não estiver conectado ao endereço do servidor,...
      alerts("Tentando", "novamente...");
      delay(500);
      lcd.clear();
      alerts("ERROR", "COD 04"); // FALHA NA CONEXÃO COM A API
    }
    alerts("Conectado!", "Conexão restaurada!");
    delay(5000);
    lcd.clear();
  }

  alerts("Conexao", "OK!");
  delay(500);
  clearBlacklight();
}

// *********************************************

void readTemp()
{
  Serial.println("Chegou aqui");
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();
  display.showNumberDec(temperatura, false, 2, 0);
  display.setSegments(celsius, 2, 2);

  lcd.setCursor(0, 0);
  lcd.print("Temperatura");
  lcd.setCursor(0, 1);
  lcd.print(temperatura);

  writeLed(temperatura);
  delay(1000);
}

void sendTemp(float temperatura, float umidade)
{
  delay(100);
  if (client.connect(serverIp, serverPort))
  {
    if (client.connected())
    {
      alerts("Salvando...", "Aguarde...");
      delay(2000);
      clearBlacklight();
      String postData = preparePostData(temperatura, umidade);
      client.println("POST http://localhost:3000/temperatura HTTP/1.1");
      client.println("Host: localhost:3000");
      client.println("Host: localhost:3000");
      client.println("Content-type: application/json");
      client.println("User-Agent: Arduino/1.0");
      client.println("Connection: close");
      client.print("Content-Length: ");
      client.println(postData.length());
      client.println();
      client.println(postData);
    }
    else 
    {
      alerts("Nao conectado", "=(");
      Serial.println("Não conectado");
    }
    delay(2000);
    clearBlacklight();
  }
}

// **************************************************

void alerts(String l1, String l2)
{
  Serial.println(l1);
  Serial.println(l2);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(l1);
  lcd.setCursor(0, 1);
  lcd.print(l2);
}

void clearBlacklight()
{
  lcd.clear();
}

void writeLed(float temperatura)
{
  Serial.println(temperatura);
  if (temperatura >= 0 && temperatura <= 25)
  {
    digitalWrite(LED_GREEN, 1);
    digitalWrite(LED_RED, 0);
  }
  digitalWrite(LED_GREEN, 0);
  digitalWrite(LED_RED, 1);
}

String preparePostData(float temperatura, float umidade)
{
  String data = "{\"temperatura\":";
  data += temperatura;
  data += ", \"umidade\":";
  data += umidade;
  data += "}";
  return data;
}

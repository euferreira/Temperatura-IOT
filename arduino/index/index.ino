#include <DHT.h>
#include <Ethernet.h>
#include <SPI.h>

#define DHTPIN A1 //pino que está conectado
#define DHTTYPE DHT11 //modulo de conexão
#define LED_VERMELHO 8
#define LED_AMARELO 9
#define LED_AZUL 5
#define LED_VERDE 2
#define LED_BRANCO 3

//Sensor de temperatura
DHT dht(DHTPIN, DHTTYPE);
float temperatura, umidade;

//ethernet
byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02}; //mac da shield ethernet
byte ip[] = { 192, 168, 0, 18 }; //ip do shield
int baudRate = 9600;
IPAddress serverIp(192, 168, 0, 20); //ip do servidor
int serverPort = 3000;
EthernetClient client;

void setup() {
  Serial.begin(baudRate);
  delay(5000);
  inicializa();

  //Tentativa de estabelecer conexão ethernet baseado em DHCP
  digitalWrite(LED_BRANCO, HIGH);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Conexão DHCP não pode ser estabelecida, Tente 'endereço de IP fixo'");
    Ethernet.begin(mac, ip); //se nenhum endereço DHCP encontrado, utilize 192.168.1.177
  }
  dht.begin();
  delay(1000);
  TesteDeConexao();
}

void loop() {
  delay(2000);
  LeTemperatura();
  ativaLed();
  Serial.println("HTTP-POST and REST Service");
  PostRestService();
  Serial.println("Execução concluida");
  Serial.println("----------------------");
  delay(10000);
}

// ---------------------------------------------------------------
//INICIALIZA OS COMPONENTES
void inicializa() {
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_BRANCO, OUTPUT);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_AZUL, LOW);
}
// ---------------------------------------------------------------

// ---------------------------------------------------------------
//CONEXOES CLIENT - SERVER
//Testa a conexão com o servidor
void TesteDeConexao() {
  Serial.println("Seu endereço de IP:");
  Serial.println(Ethernet.localIP());
  delay(2000);

  Serial.println("Testando conexão com servidor:");
  if (client.connect(serverIp, serverPort)) {
    digitalWrite(LED_BRANCO, LOW);
    Serial.println("Conectado ao servidor. fechando conexão");
    client.stop();
    Serial.println("conexão encerrada");
  }
  else {
    Serial.println("Erro: Não foi possível se conectar ao servidor...");
    Serial.println("------------------------------------");
    Serial.println();
  }
}

//Realiza um post na API
void PostRestService() {
  if (client.connect(serverIp, 3000))
  {
    Serial.println("Conectado ao servidor.");
    String PostData = "{\"temperatura\":";
    PostData += temperatura;
    PostData += ", \"umidade\":";
    PostData += umidade;
    PostData += "}";
    Serial.println(PostData);

    if (client.connected()) {
      Serial.println("connected");
      client.println("POST http://localhost:3000/api/temperatura HTTP/1.1");
      client.println("Host: localhost:3000");
      client.println("Host: localhost:3000");
      client.println("Content-Type: application/json"); // Pode enviar conteúdo como JSON, então ASP.net MVC WebAPI negócio corretamente com ele
      client.println("User-Agent: Arduino/1.0");
      client.println("Connection: close");
      client.print("Content-Length: ");
      client.println(PostData.length());
      client.println();
      client.println(PostData);
      
      digitalWrite(LED_VERDE, HIGH);
      while (!client.available()) {}
      Serial.print("======> Client disponível:");
      Serial.println(client.available());
      Serial.print("======> Client conectado:");
      Serial.println(client.connected());
      
      if (client.available()) {
        digitalWrite(LED_VERDE, LOW);
        char c = client.read();
        
        Serial.println(c);
      }
      if (!client.connected()) {
        Serial.println();
        Serial.println("disconnecting.");
        Serial.println("=======================");
        client.stop();
      }
    } else {
      Serial.println("connection failed");
    }
  }
  else
  {
    Serial.println("Não foi possível conectar ao servidor!");
  }
}
// ---------------------------------------------------------------

// ---------------------------------------------------------------
//sensor de temperatura
void LeTemperatura() {
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  umidade = dht.readHumidity();
  temperatura = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(temperatura) || isnan(umidade))
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" *C");
  }
}
// ---------------------------------------------------------------

// ---------------------------------------------------------------
//LED
void ativaLed() {
  if (temperatura >= 0 && temperatura <= 18) {
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_AZUL, HIGH);
  }
  else if (temperatura > 18 && temperatura <= 25) {
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_AZUL, LOW);
  }
  else {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_AZUL, LOW);
  }
}
// ---------------------------------------------------------------

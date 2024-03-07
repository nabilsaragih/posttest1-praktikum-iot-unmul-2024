#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED1 D0  // Pemilihan Pin D0
#define LED2 D2  // Pemilihan Pin D1

const char* ssid = "Universitas Mulawarman";                // Nama SSID AP/Hotspot
const char* password = "";  // Password Wifi1

ESP8266WebServer server(80);  //Menyatakan Webserver pada port 80
String webpage;

void setup() {  //Pengaturan Pin
  Serial.begin(115200);
  delay(10);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Connect ke WiFi
  Serial.println();
  Serial.print("Configuring access point...");

  // Mengatur WiFi
  WiFi.mode(WIFI_STA);  // Mode Station
  // WiFi.mode(WIFI_AP);                      // Mode AP
  WiFi.begin(ssid, password);  // Mencocokan SSID dan Password

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print status Connect
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // Serial.println(WiFi.softAPIP());

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  // digitalWrite(LED_BUILTIN, LOW);

  // Isi dari Webpage
  webpage += "<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH\" crossorigin=\"anonymous\">";
  webpage += "<h1 style='text-align: center;'>Web Control LED ESP8266</h1>";
  webpage += "<div class='d-flex justify-content-center'>";
  webpage += "<a href='LED1ON' style='text-decoration: none;'><button style='padding: 10px; margin: 5px; border: none; border-radius: 5px;' class='bg-primary text-light'>LED1 ON</button></a>";
  webpage += "<a href='LED2ON' style='text-decoration: none;'><button style='padding: 10px; margin: 5px; border: none; border-radius: 5px;' class='bg-primary text-light'>LED2 ON</button></a>";
  webpage += "<a href='LEDOFF' style='text-decoration: none;'><button style='padding: 10px; margin: 5px; border: none; border-radius: 5px;' class='bg-danger text-light'>OFF ALL LED</button></a>";
  webpage += "</div>";
  
  // Membuat file webpage
  server.on("/", []() {
    server.send(200, "text/html", webpage);
  });

  // Bagian ini untuk merespon perintah yang masuk
  server.on("/LED1ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  });
  server.on("/LED2ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
  });
  server.on("/LEDOFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  });

  server.begin();
  Serial.println("Server dijalankan");
}

void loop() {  //Perulangan Program
  server.handleClient();
}
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>



/* Set these to your desired credentials. */
const char *ssid = "your-ssid";
const char *password = "your-pass";


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 10);//the ip for the esp8266
IPAddress sub(255, 255, 255, 0);//the subnet for the esp8266
IPAddress gw(192, 168, 1, 1);//the gateway for the esp8266

unsigned int localPort = 6000;      // local port to listen on



int statusled1=13;
int relay1=12;

int state1 = LOW;


// buffers for receiving and sending data
char packetBuffer[50]; //buffer to hold incoming packet,

// An wifiUDP instance to let us send and receive packets over UDP
WiFiUDP Udp;


void setup() {

  Serial.begin(115200);

  Serial.print("Configuring station...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.begin(ssid, password);


while (WiFi.status() != WL_CONNECTED) {
    delay(500);
Serial.print(".");
  }

//for static ip address
//config (local_ip, gateway, subnet)
  WiFi.config(ip,gw,sub);

 Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());




  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");

  pinMode(relay1, OUTPUT);
  pinMode(statusled1, OUTPUT);

  
  Udp.begin(localPort);

  
digitalWrite(relay1, state1);
digitalWrite(statusled1, !state1);

}

void loop() {
  
 
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    
    if(packetBuffer[0]=='A'){
    state1 = HIGH;  
    digitalWrite(relay1,state1);
    digitalWrite(statusled1, !state1);
    
    }
    
      if(packetBuffer[0]=='a'){    
        state1 = LOW;
    digitalWrite(relay1,state1);
     digitalWrite(statusled1, !state1); 
    
      }
  }
  delay(10);
}

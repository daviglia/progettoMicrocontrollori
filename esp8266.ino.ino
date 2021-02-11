//includo le librerie necessarie al modulo
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//imposto nome e password della rete a cui devo collegarmi
const char *nome_rete = "Rete 2.4 GHz";
const char *password_rete = "25041998";

String ip_interfaccia;

//imposto la porta di accesso del server web
ESP8266WebServer server (80);

//inizializzo il modulo
void setup ( void ) {

  //apro la seriale sul baudrate 115200 di default
  Serial.begin (115200);

  //inizializzo la connessione alla rete wifi
	WiFi.begin (nome_rete, password_rete);

  //scrivo la prima riga vuota per mandare a capo
	Serial.println ("");

  //scrivo i puntini per indicare che il modulo sta connettendosi al wifi ogni 500 millisecondi fino a quando la connessione non si è stabilita
	while ( WiFi.status() != WL_CONNECTED ) {
		delay (500);
		Serial.print (".");
	}

  //scrivo i dati relativi alla connessione per verificare che tutto sia ok
	Serial.println ( "" );
	Serial.print ("Connesso alla rete : ");
	Serial.println (nome_rete);
	Serial.print ("Pagina di controllo raggiungibile da : http://");
	Serial.println (WiFi.localIP());

  //scrivo "Modulo pronto!" non appena la connessione è stata stabilita e l'esp8266 è connesso
	if (MDNS.begin ("esp8266")) {
		Serial.println ("Modulo pronto!");
	}

  //imposto i comandi di get da prendere in considerazione e la relativa funzione correlata
  server.on("/", interfaccia);
	server.on("/uscita1", uscita1);
	server.on("/uscita2", uscita2);
  server.on("/uscita3", uscita3);
  server.on("/uscita4", uscita4);
  server.on("/uscita5", uscita5);
  server.on("/uscita6", uscita6);
  server.on("/uscita7", uscita7);
  server.on("/uscita8", uscita8);

  //avvio il server
	server.begin();

  //scrivo che il server http è stato avviato
	Serial.println ("Server HTTP avviato!");
  
}


void loop ( void ) {
  //mantengo il server in attesa
	server.handleClient();
}

void interfaccia() {
    //costruisco l'interfaccia del server
    server.send(200, "text/html", "<!DOCTYPE html><html><head><title>Pulsantiera virtuale</title><style> .button{font-size: 60px;height: 200px;width: 100%;} .littleButton{float:left;font-size: 60px;height: 200px;width: 50%;}h3{margin-left:auto;margin-right:auto;width:200px;}</style></head><body><h3>Pulsantiera virtuale</h3><button class='button' onclick='location.href=&#39;/uscita1&#39;' lengh>Accendi</button><br /><br /><button  class='button' onclick='location.href=&#39;/uscita2&#39;'>Spegni</button><br /><br /><button  class='littleButton' onclick='location.href=&#39;/uscita3&#39;'>+</button><button class='littleButton' onclick='location.href=&#39;/uscita4&#39;'>-</button><br /><br /><button  class='button' onclick='location.href=&#39;/uscita5&#39;'>Rosso</button><br /><br /><button  class='button' onclick='location.href=&#39;/uscita6&#39;'>Blu</button><br /><br /><button   class='button' onclick='location.href=&#39;/uscita7&#39;'>Verde</button><br /><br /><button   class='button' onclick='location.href=&#39;/uscita8&#39;'>Bianco</button></body></html>");
}

void uscita1() {
  //richiama uscita 1
Serial.println('1');
  interfaccia();
}
void uscita2() {
  //richiama uscita 2
Serial.println('2');
  interfaccia();
}
void uscita3() {
  //richiama uscita 3
Serial.println('3');
  interfaccia();
}
void uscita4() {
  //richiama uscita 4
Serial.println('4');
  interfaccia();
}
void uscita5() {
  //richiama uscita 5
Serial.println('5');
  interfaccia();
}
void uscita6() {
  //richiama uscita 6
Serial.println('6');
  interfaccia();
}
void uscita7() {
  //richiama uscita 7
Serial.println('7');
  interfaccia();
}
void uscita8() {
  //richiama uscita 8
Serial.println('8');
  interfaccia();
}

/*
Import des bibliothèques
*/
  #include <ESP8266WiFi.h>
  #include <ESP8266WiFiMulti.h>
  #include <ESP8266WebServer.h>
  #include <ESP8266mDNS.h>
  #include <FS.h>
/**/

/*
Création du serveur
*/
  // Instanciation de la class ESP8266WiFiMulti
  ESP8266WiFiMulti wifiMulti;
  
  // Création du serveur Web sur le port 80
  ESP8266WebServer server = ESP8266WebServer(80);
/**/


/*
Définition des identifiants réseau
*/
  // Réseau local
  const char *ssid = "CoffeeMachineECV";
  const char *password = "ecvecvecv";

  // Réseau Wifi
  const char *ssidWifi = "XXX";
  const char *passwordWifi = "XXX";
  
  // Nom de domaine du serveur : fini par .local
  const char* mdnsName = "coffee-machine";
/**/

/*
Définition des PINs
*/
  // Relais de la machine à café
  const int coffeePin = 12; /*Wemos PIN D6*/
  const int sugarPin = 13; /*Wemos PIN D7*/
  const int waterPin = 2; /*Wemos PIN D4*/
//



/*
Setup de la carte
*/
  void setup() {
    // Délai avant nouvelle tentative
    delay(1000);
    
    // Définition des PINS de la carte
    pinMode(coffeePin, OUTPUT);
    pinMode(sugarPin, OUTPUT);
    pinMode(waterPin, OUTPUT);
  
    // Fermer les PINS de la carte
    digitalWrite(coffeePin, LOW);
    digitalWrite(sugarPin, LOW);
    digitalWrite(waterPin, LOW);

    // Définition de la vitesse de communication
    Serial.begin(115200);
    delay(10);
    Serial.println("\r\n");

    // Démarrer le WiFi
    startWiFi();

    // Démarrer MDNS
    startMDNS();

    // Démarrer le gestionnaire de fichier
    startSPIFFS();

    // Démarrer le serveur HTTP
    startServer();    
  }
/**/



/*
Boucle de la carte
*/
  void loop() {
    // Lancer le serveur
    server.handleClient();
  }
/**/



/*
Gestionnaire des séquences pour le café
*/
  // Faire un café sans sucre
  void handleCoffee() {
    delay(600);
    digitalWrite(coffeePin, HIGH);
    delay(2000);
    digitalWrite(coffeePin, LOW);
    digitalWrite(waterPin, HIGH);
    delay(4000);
    digitalWrite(waterPin, LOW);
  }

  // Faire un café avec sucre
  void handleSweetCoffee() {
    delay(600);
    digitalWrite(coffeePin, HIGH);
    delay(2000);
    digitalWrite(coffeePin, LOW);
    digitalWrite(sugarPin, HIGH);
    delay(1000);
    digitalWrite(sugarPin, LOW);
    digitalWrite(waterPin, HIGH);
    delay(4000);
    digitalWrite(waterPin, LOW);
  }
/**/



/*
Gestion de la connexion WiFi
*/
  void startWiFi() {
    
    // Création de l'Access Point
    Serial.println("");
    WiFi.mode(WIFI_STA);
    WiFi.softAP(ssid, password);
    Serial.print("Création de l'Access Point : ");
    Serial.println(ssid);

    // Ajouter une connexion au réseau distant (plusieurs connexions possible)
    wifiMulti.addAP(ssidWifi, passwordWifi);

    // Connexion au réseau
    Serial.println("Connexion");
    while (wifiMulti.run() != WL_CONNECTED && WiFi.softAPgetStationNum() < 1) {
      delay(250);
      Serial.print('.');
    }
    Serial.println("\r\n");

    // Vérification de la connexion réseau
    if(WiFi.softAPgetStationNum() == 0) {
      Serial.print("Serveur connecté au réseau : ");
      Serial.println(WiFi.SSID());
      Serial.println("");
      Serial.print("Adresse du serveur sur le réseau ");
      Serial.print(ssid);
      Serial.print(" : http://");
      Serial.print(WiFi.localIP());
      
    } else {
      Serial.print("Station connecté à ESP8266 AP");
    }
    //Serial.println("\r\n");
  }
/**/


/*
Gestionnaire de fichiers
*/
  void startSPIFFS() {
  
    // Démarrer le gestionnaire de fichiers
    SPIFFS.begin();
  
    /*
    Vider la mémoire
    */
      SPIFFS.remove("/index.html");
      SPIFFS.remove("/style.css");
      SPIFFS.remove("/script.js");
      SPIFFS.remove("/data/data.json");
    /**/
    
    /*
    Ecriture du fichier style.css
    */
      // Création du fichier
      File style = SPIFFS.open("/css/style.css", "w");
      if (!style) {
          Serial.println("Impossible d'ouvrir le fichier...");
      };
  
      // Ecriture du fichier
      Serial.println("");
      Serial.println("Ecriture du fichier style.css...");
      style.print("button,fieldset{border:none}#mainTitle,button{cursor:pointer}.coffeeType,h2,h2 span{position:relative}.nextBtn,footer,h1,h2 span{text-transform:uppercase}*{margin:0;padding:0;-webkit-box-sizing:border-box;-moz-box-sizing:border-box;box-sizing:border-box}:focus{outline:0}html{font-size:62.5%}body{font-size:1.5rem;font-family:sans-serif;font-weight:300;opacity:0;-webkit-transition:opacity .5s;transition:opacity .5s}b,button span,h1 span{font-weight:700}body.open{opacity:1}a{color:inherit;text-decoration:none}button{display:block;width:100%;background:0 0;-webkit-transition:all .3s;transition:all .3s}button.active{background-color:#eee}button#blackCoffee.active{background-color:#c9c9c9}.coffeePicto{width:9rem;height:9rem;margin:0 auto 1.5rem;-webkit-transform:translateX(1rem);transform:translateX(1rem)}.coffeePicto .line div{width:11.11111%}.coffeePicto .line:nth-child(1){height:15%}.coffeePicto .line{display:-webkit-flex;display:flex;height:10%}.fifthLine,.firstLine:nth-child(2),.firstLine:nth-child(4),.firstLine:nth-child(6),.forthLine,.heigthLine,.ninethLine,.secondeLine:nth-child(1),.secondeLine:nth-child(3),.secondeLine:nth-child(5),.seventhLine,.sixthLine,.tenthLine,.thridLine:nth-child(2),.thridLine:nth-child(4),.thridLine:nth-child(6){background:#000}.fifthLine:nth-child(4),.fifthLine:nth-child(8),.forthLine:nth-child(7),.forthLine:nth-child(9),.heigthLine:nth-child(4),.heigthLine:nth-child(8),.heigthLine:nth-child(9),.ninethLine:nth-child(4),.ninethLine:nth-child(7),.ninethLine:nth-child(8),.ninethLine:nth-child(9),.seventhLine:nth-child(4),.seventhLine:nth-child(7),.seventhLine:nth-child(9),.sixthLine:nth-child(4),.sixthLine:nth-child(7),.sixthLine:nth-child(8),.tenthLine:nth-child(1),.tenthLine:nth-child(6),.tenthLine:nth-child(7),.tenthLine:nth-child(8),.tenthLine:nth-child(9){background-color:transparent}.line:nth-child(1){opacity:.3}.line:nth-child(2){opacity:.5}.line:nth-child(3){opacity:.7}h2 span,h2.hidden{opacity:0}footer,header,main{width:100%;max-width:35rem;margin:2rem auto}header{margin-top:4rem}h1{font-size:3.4rem;line-height:1}h1 span{font-size:1.5rem;display:block}h1 span:last-child{margin-top:.4rem;font-weight:300;font-size:1.3rem;border-bottom:.1rem solid #eee;padding-bottom:1rem}h2{font-size:1.8rem;margin-bottom:.7rem;-webkit-transition:all .3s;transition:all .3s}h2 span{font-size:1rem;color:#fff;background:#402a0c;padding:.2rem .5rem;top:-.2rem;-webkit-transition:opacity .3s;transition:opacity .3s}h2 span.open{opacity:1}[type=radio]{display:none}#formStepOne article{display:-webkit-flex;display:flex;-webkit-justify-content:space-between;-moz-justify-content:space-between;justify-content:space-between}#formStepOne{opacity:1;-webkit-transition:opacity .3s;transition:opacity .3s}#formStepOne.close{opacity:0}.coffeeType{height:17rem;width:48%;margin:1.3rem auto 2rem;border:.1rem dotted #eee}.coffeePicto{-webkit-transition:all .2s;transition:all .3s;-webkit-transition-timing-function:ease-in-out;transition-timing-function:ease-in-out}.coffeeType:focus .coffeePicto,.coffeeType:hover .coffeePicto{width:11rem;height:11rem}.coffeeType a{position:absolute;top:0;left:0;height:100%;width:100%;z-index:1}.fa-coffee{display:block;font-size:8rem}[data-coffee=sweet] .fa{color:#3f290c}.nextBtn{font-size:1.1rem;font-weight:700;background:#eee;padding:1rem 0}.nextBtn:focus,.nextBtn:hover,.randomChoices:focus,.randomChoices:hover{background-color:#c9c9c9}#randomQuestion{height:0;opacity:0;-webkit-transition:opacity .3s;transition:opacity .3s}#randomQuestion.open{opacity:1;height:20rem}#newOrderBtn,#restartBtn,.randomChoices{text-align:left;font-size:1.3rem;font-weight:100;padding:1rem;border:.1rem solid #eee;margin:1rem auto}#newOrderBtn,#restartBtn{font-weight:700;border-color:#000;opacity:0;-webkit-transition:opacity .3s;transition:opacity .3s}#waiter{opacity:0;-webkit-transition:opacity .3s;transition:opacity .3s}#newOrderBtn.open,#restartBtn.open,#waiter.open{opacity:1}footer{font-size:1rem;font-weight:700;color:grey;position:fixed;bottom:0;left:50%;-webkit-transform:translateX(-50%);transform:translateX(-50%)}footer span{display:block;font-weight:300}");
      style.close();
    
      // Vérification du fichier
      style = SPIFFS.open("/css/style.css", "r");
      if (style) {
          Serial.println("Fichier style.css créé !");
          // Serial.println("Contenu du fichier :");
          // Serial.println(style.readStringUntil('\n'));
      }
    /**/
  
    /*
    Ecriture des fichiers JSON
    */
      // Création du fichier
      File blackCoffee = SPIFFS.open("/data/blackCoffee.json", "w");
      if (!blackCoffee) {
          Serial.println("Impossible d'ouvrir le fichier...");
      };
  
      // Ecriture du fichier
      Serial.println("");
      Serial.println("Ecriture du fichier...");
      blackCoffee.print("{\"response\": \"blackCoffee\"}");
      blackCoffee.close();
    
      // Vérification du fichier
      blackCoffee = SPIFFS.open("/data/blackCoffee.json", "r");
      if (blackCoffee) {
          Serial.println("Fichier blackCoffee.json créé !");
          // Serial.println("Contenu du fichier :");
          // Serial.println(style.readStringUntil('\n'));
      }

      // Création du fichier
      File sweetCoffee = SPIFFS.open("/data/sweetCoffee.json", "w");
      if (!sweetCoffee) {
          Serial.println("Impossible d'ouvrir le fichier...");
      };
  
      // Ecriture du fichier
      Serial.println("");
      Serial.println("Ecriture du fichier...");
      sweetCoffee.print("{\"response\": \"sweetCoffee\"}");
      sweetCoffee.close();
    
      // Vérification du fichier
      sweetCoffee = SPIFFS.open("/data/sweetCoffee.json", "r");
      if (sweetCoffee) {
          Serial.println("Fichier sweetCoffee.json créé !");
          // Serial.println("Contenu du fichier :");
          // Serial.println(style.readStringUntil('\n'));
      }
    /**/
  
    
    /*
    Ecriture du fichier script.js
    */
      // Création du fichier
      File script = SPIFFS.open("/js/script.js", "w");
      if (!script) {
          Serial.println("Impossible d'ouvrir le fichier...");
      }
  
      // Ecriture du fichier
      Serial.println("");
      Serial.println("Ecriture du fichier script.js...");
      script.print("document.addEventListener('DOMContentLoaded', function(event) {window.setTimeout(function(){document.querySelector('body').classList.add('open');}, 300);var coffeeBtns = document.querySelectorAll('.coffeeType');var userSelection = null;var myH2title = document.getElementById('myH2title');var randomQuestion = document.getElementById('randomQuestion');var formStepOne = document.getElementById('formStepOne');var waiter = document.getElementById('waiter');var restartBtn = document.getElementById('restartBtn');var newOrderBtn = document.getElementById('newOrderBtn');var blackCoffee = document.getElementById('blackCoffee');var sweetCoffee = document.getElementById('sweetCoffee');var errorMessage = document.getElementById('errorMessage');var randomQuestionList = document.getElementById('randomQuestionList');var randomQuestionTitle = document.getElementById('randomQuestionTitle');var questionsArray = [{id: 1,question: 'When did the first website appear?',choices: [{id: 1,proposal: 'January 17th, 1999',response: false},{id: 2,proposal: 'September 23th, 1994',response: false},{id: 3,proposal: 'August 6th, 1991',response: true}]},{id: 2,question: 'Who invented the web?',choices: [{id: 1,proposal: 'Bob Kahn',response: false},{id: 2,proposal: 'Timothy Berners Lee',response: true},{id: 3,proposal: 'Issac Asimov',response: false}]},{id: 3,question: 'What is the definition of http?',choices: [{id: 1,proposal: 'Hypertext Transfer Protocol',response: true},{id: 2,proposal: 'Hyper Text Protocol',response: false},{id: 3,proposal: 'Hypertext Technology Protocol',response: false}]},{id: 4,question: 'What statement is not accurate?',choices: [{id: 1,proposal: 'A robot must obey the orders given by human beings.',response: false},{id: 2,proposal: 'A robot must protect its integrity against aggression.',response: true},{id: 3,proposal: 'A robot can not leave a human beings exposed to danger.',response: false}]},{id: 4,question: 'Easy for you, what does ECV mean?',choices: [{id: 1,proposal: 'École de Communication Visuelle.',response: true},{id: 2,proposal: 'Envie de Croire en Vous.',response: false},{id: 3,proposal: 'Etre Conscient-e de vos Valeurs.',response: false}]}];var randomQuestionNumber = Math.floor((Math.random() * 5) + 0);var randomChoicesArray = questionsArray[randomQuestionNumber].choices;randomQuestionTitle.textContent = questionsArray[randomQuestionNumber].question;for(var i = 0; i < randomChoicesArray.length; i++){var newChoiceBtn = document.createElement('button');newChoiceBtn.textContent = randomChoicesArray[i].proposal;newChoiceBtn.setAttribute('data-choice', randomChoicesArray[i].response);newChoiceBtn.classList.add('randomChoices');randomQuestionList.appendChild(newChoiceBtn);};var randomChoices = document.querySelectorAll('.randomChoices');for(var i = 0; i < coffeeBtns.length; i++){coffeeBtns[i].onclick = function(){blackCoffee.classList.remove('active');sweetCoffee.classList.remove('active');this.classList.add('active');userSelection = this.getAttribute('data-coffee');};};document.getElementById('goToStep2').onclick = function(){if(userSelection != null){myH2title.classList.add('hidden');formStepOne.classList.add('close');window.setTimeout(function(){formStepOne.style.display = 'none';myH2title.textContent = 'Select the correct response';myH2title.classList.remove('hidden');                    window.setTimeout(function(){randomQuestion.style.display = 'block';randomQuestion.classList.add('open');}, 300);}, 300);} else{errorMessage.classList.add('open');window.setTimeout(function(){errorMessage.classList.remove('open');}, 5000);};};for(var i = 0; i < randomChoices.length; i++){randomChoices[i].onclick = function(){myH2title.classList.add('hidden');randomQuestion.classList.remove('open');window.setTimeout(function(){randomQuestion.style.display = 'none';}, 300);if(this.getAttribute('data-choice') == 'true'){window.setTimeout(function(){myH2title.textContent = 'Your order is complete';myH2title.classList.remove('hidden');waiter.classList.add('open');}, 300);fetchJSONFile(userSelection, function(data){console.log(data);myH2title.classList.add('hidden');waiter.classList.remove('open');window.setTimeout(function(){waiter.style.display = 'none';restartBtn.style.display = 'none';myH2title.textContent = 'Enjoy your coffee!';myH2title.classList.remove('hidden');newOrderBtn.classList.add('open');}, 300);});} else{window.setTimeout(function(){waiter.style.display = 'none';myH2title.textContent = 'Bad response...';myH2title.classList.remove('hidden');restartBtn.classList.add('open');}, 300);};};};function restart(){document.querySelector('body').classList.remove('open');window.setTimeout(function(){location.reload();}, 500);};restartBtn.onclick = function(){restart();};newOrderBtn.onclick = function(){restart();};document.getElementById('mainTitle').onclick = function(){restart();};function fetchJSONFile(path, callback) {var httpRequest = new XMLHttpRequest();httpRequest.onreadystatechange = function() {if (httpRequest.readyState === 4) {if (httpRequest.status === 200) {var data = JSON.parse(httpRequest.responseText);if (callback) callback(data);}}};httpRequest.open('GET', './' + path);httpRequest.send(); }});");
      script.close();
    
      // Vérification du fichier
      script = SPIFFS.open("/js/script.js", "r");
      if (script) {
          Serial.println("Fichier script.js créé !");
          // Serial.println("Contenu du fichier :");
          // Serial.println(script.readStringUntil('\n'));
      }  
    /**/
    
    
    /*
    Ecriture du fichier index.html
    */
      // Création du fichier
      File index = SPIFFS.open("/index.html", "w");
      if (!index) {
          Serial.println("Impossible d'ouvrir le fichier...");
      }
  
      // Ecriture du fichier
      Serial.println("");
      Serial.println("Ecriture du fichier index.html...");
      index.print("<!DOCTYPE html><html lang='en'> <head> <meta charset='UTF-8'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <meta http-equiv='X-UA-Compatible' content='ie=edge'> <title>ECD Digital : The CoffeeMachine</title> <link rel='stylesheet' href='./css/style.css'> </head> <body> <header> <h1><span>The connected</span> <b id='mainTitle'>CoffeeMachine</b> <span>Inside ECV Digital</span></h1> </header> <main> <h2 id='myH2title'>Choose your pleasure <span id='errorMessage'>Choose one coffee</span></h2> <section id='formStepOne'> <article> <button id='blackCoffee' class='coffeeType' data-coffee='blackCoffee'> <div class='coffeePicto'> <div class='line'> <div class='firstLine'></div><div class='firstLine'></div><div class='firstLine'></div><div class='firstLine'></div><div class='firstLine'></div><div class='firstLine'></div><div class='firstLine'></div><div class='firstLine'></div><div class='firstLine'></div></div><div class='line'> <div class='secondeLine'></div><div class='secondeLine'></div><div class='secondeLine'></div><div class='secondeLine'></div><div class='secondeLine'></div><div class='secondeLine'></div><div class='secondeLine'></div><div class='secondeLine'></div><div class='secondeLine'></div></div><div class='line'> <div class='thridLine'></div><div class='thridLine'></div><div class='thridLine'></div><div class='thridLine'></div><div class='thridLine'></div><div class='thridLine'></div><div class='thridLine'></div><div class='thridLine'></div><div class='thridLine'></div></div><div class='line'> <div class='forthLine'></div><div class='forthLine'></div><div class='forthLine'></div><div class='forthLine'></div><div class='forthLine'></div><div class='forthLine'></div><div class='forthLine'></div><div class='forthLine'></div><div class='forthLine'></div></div><div class='line'> <div class='fifthLine'></div><div class='fifthLine'></div><div class='fifthLine'></div><div class='fifthLine'></div><div class='fifthLine'></div><div class='fifthLine'></div><div class='fifthLine'></div><div class='fifthLine'></div><div class='fifthLine'></div></div><div class='line'> <div class='sixthLine'></div><div class='sixthLine'></div><div class='sixthLine'></div><div class='sixthLine'></div><div class='sixthLine'></div><div class='sixthLine'></div><div class='sixthLine'></div><div class='sixthLine'></div><div class='sixthLine'></div></div><div class='line'> <div class='seventhLine'></div><div class='seventhLine'></div><div class='seventhLine'></div><div class='seventhLine'></div><div class='seventhLine'></div><div class='seventhLine'></div><div class='seventhLine'></div><div class='seventhLine'></div><div class='seventhLine'></div></div><div class='line'> <div class='heigthLine'></div><div class='heigthLine'></div><div class='heigthLine'></div><div class='heigthLine'></div><div class='heigthLine'></div><div class='heigthLine'></div><div class='heigthLine'></div><div class='heigthLine'></div><div class='heigthLine'></div></div><div class='line'> <div class='ninethLine'></div><div class='ninethLine'></div><div class='ninethLine'></div><div class='ninethLine'></div><div class='ninethLine'></div><div class='ninethLine'></div><div class='ninethLine'></div><div class='ninethLine'></div><div class='ninethLine'></div></div><div class='line'> <div class='tenthLine'></div><div class='tenthLine'></div><div class='tenthLine'></div><div class='tenthLine'></div><div class='tenthLine'></div><div class='tenthLine'></div><div class='tenthLine'></div><div class='tenthLine'></div><div class='tenthLine'></div></div></div><span>Black coffee</span> </button> <button id='sweetCoffee' class='coffeeType' data-coffee='sweetCoffee'> <div class='coffeePicto'> <div class='line'> <div class='firstLine'></div><div class='firstLine'></div><div class='firstLine'></div><div class='firstLine'></div><div class='firstLine'></div><div class='firstLine'></div><div class='firstLine'></div><div class='firstLine'></div><div class='firstLine'></div></div><div class='line'> <div class='secondeLine'></div><div class='secondeLine'></div><div class='secondeLine'></div><div class='secondeLine'></div><div class='secondeLine'></div><div class='secondeLine'></div><div class='secondeLine'></div><div class='secondeLine'></div><div class='secondeLine'></div></div><div class='line'> <div class='thridLine'></div><div class='thridLine'></div><div class='thridLine'></div><div class='thridLine'></div><div class='thridLine'></div><div class='thridLine'></div><div class='thridLine'></div><div class='thridLine'></div><div class='thridLine'></div></div><div class='line'> <div class='forthLine'></div><div class='forthLine'></div><div class='forthLine'></div><div class='forthLine'></div><div class='forthLine'></div><div class='forthLine'></div><div class='forthLine'></div><div class='forthLine'></div><div class='forthLine'></div></div><div class='line'> <div class='fifthLine'></div><div class='fifthLine'></div><div class='fifthLine'></div><div class='fifthLine'></div><div class='fifthLine'></div><div class='fifthLine'></div><div class='fifthLine'></div><div class='fifthLine'></div><div class='fifthLine'></div></div><div class='line'> <div class='sixthLine'></div><div class='sixthLine'></div><div class='sixthLine'></div><div class='sixthLine'></div><div class='sixthLine'></div><div class='sixthLine'></div><div class='sixthLine'></div><div class='sixthLine'></div><div class='sixthLine'></div></div><div class='line'> <div class='seventhLine'></div><div class='seventhLine'></div><div class='seventhLine'></div><div class='seventhLine'></div><div class='seventhLine'></div><div class='seventhLine'></div><div class='seventhLine'></div><div class='seventhLine'></div><div class='seventhLine'></div></div><div class='line'> <div class='heigthLine'></div><div class='heigthLine'></div><div class='heigthLine'></div><div class='heigthLine'></div><div class='heigthLine'></div><div class='heigthLine'></div><div class='heigthLine'></div><div class='heigthLine'></div><div class='heigthLine'></div></div><div class='line'> <div class='ninethLine'></div><div class='ninethLine'></div><div class='ninethLine'></div><div class='ninethLine'></div><div class='ninethLine'></div><div class='ninethLine'></div><div class='ninethLine'></div><div class='ninethLine'></div><div class='ninethLine'></div></div><div class='line'> <div class='tenthLine'></div><div class='tenthLine'></div><div class='tenthLine'></div><div class='tenthLine'></div><div class='tenthLine'></div><div class='tenthLine'></div><div class='tenthLine'></div><div class='tenthLine'></div><div class='tenthLine'></div></div></div><span>Coffee with sugar</span> </button> </article> <button id='goToStep2' class='nextBtn'>Next step</button> </section> <section id='randomQuestion'> <p id='randomQuestionTitle'></p><article id='randomQuestionList'></article> </section> <p id='waiter'>Processing...</p><button id='restartBtn'>Restart your order</button> <button id='newOrderBtn'>New order</button> </main> <footer> <p> <a href='https://github.com/DWS-paris/WEMOSwebServer' target='_blank'>Under MIT Licence</a> / 2017 <span> <a href='https://www.linkedin.com/in/anthonybaillard/' target='_blank'>Anthonny Baillard</a> - <a href='https://www.linkedin.com/in/damient75/' target='_blank'>Damien Truffaut</a> - <a href='https://www.linkedin.com/in/julien-noyer-21219b28/' target='_blank'>Julien Noyer</a> </span> </p></footer> <script src='./js/script.js'></script> </body></html>");
      index.close();
    
      // Vérification du fichier
      index = SPIFFS.open("/index.html", "r");
      if (index) {
          Serial.println("Fichier index.html créé !");
          // Serial.println("Contenu du fichier :");
          // Serial.println(index.readStringUntil('\n'));
      }
    /**/
  
  
    /*
    Afficher la liste des fichiers
    */
      Serial.println("");
      Serial.println("Liste des fichiers contenus dans la carte :");{
        Dir dir = SPIFFS.openDir("/");
        while (dir.next()) {
          String fileName = dir.fileName();
          size_t fileSize = dir.fileSize();
          Serial.printf("- %s (%s)\r\n", fileName.c_str(), formatBytes(fileSize).c_str());
        }
        Serial.printf("\n");
      }
    /**/

    
  }
/**/

/*
Conversion de la taille des fichiers
*/
  String formatBytes(size_t bytes) { // convert sizes in bytes to KB and MB
    if (bytes < 1024) {
      return String(bytes) + "B";
    } else if (bytes < (1024 * 1024)) {
      return String(bytes / 1024.0) + "KB";
    } else if (bytes < (1024 * 1024 * 1024)) {
      return String(bytes / 1024.0 / 1024.0) + "MB";
    }
  }
/**/

/*
Définir le type de fichier
*/
  String getContentType(String filename) { // determine the filetype of a given filename, based on the extension
    if (filename.endsWith(".html")) return "text/html";
    else if (filename.endsWith(".css")) return "text/css";
    else if (filename.endsWith(".js")) return "application/javascript";
    else if (filename.endsWith(".json")) return "application/json";
    else if (filename.endsWith(".ico")) return "image/x-icon";
    else if (filename.endsWith(".gz")) return "application/x-gzip";
    return "text/plain";
  }
/**/


/*
Gestionnaire du nom de domaine
*/
  void startMDNS() {
    // Démarrer le gestionnaire de DNS
    MDNS.begin(mdnsName);
    Serial.println("");
    Serial.print("Adresse du serveur sur le réseau ");
    Serial.print(ssidWifi);
    Serial.print(" : http://");
    Serial.print(mdnsName);
    Serial.println(".local");
  }
/**/



/*
Gestionnaire du serveur HTTP
*/
  void startServer() {
    // Gestion des erreur 404
    server.onNotFound(handleNotFound);

    // Démarrer le serveur
    server.begin();
    Serial.println("");
    Serial.println("Serveur HTTP démarré.");
  }
/**/


/*
Gestion des erreurs 404
*/
  void handleNotFound(){
    if(!handleFileRead(server.uri())){
      // Renvoyer l'erreur 404
      server.send(404, "text/plain", "404: Fichier non trouvé");
    }
  }
/**/

/*
Gestion des fichiers des routes
*/
  bool handleFileRead(String path) {
    Serial.println("");
    Serial.println("Requete sur la route : " + path);

    // Définitions des fichiers à envoyer selon les routes
    if (path.endsWith("/")) path += "index.html";
    if (path.endsWith("/data")) path += "/data.json";
    
    if (path.endsWith("/blackCoffee")) {
      // Renvoyer un objet JSON
      path = "/data/blackCoffee.json";
      
      // Activer la machine à café
      handleCoffee();
    };

    if (path.endsWith("/sweetCoffee")) {
      // Renvoyer un objet JSON
      path = "/data/sweetCoffee.json";
      
      // Activer la machine à café
      handleSweetCoffee();
    };
  
    // Identification du type de fichier
    String contentType = getContentType(path);
    String pathWithGz = path + ".gz";

    // Vérification de la présence du fichier
    if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {

      // Vérification si une version compressée est disponible
      if (SPIFFS.exists(pathWithGz)) path += ".gz";

      // Si une version compressée n'éxiste pas, ouvrir le fichier normal
      File file = SPIFFS.open(path, "r");
      // Envoyer le fichier au client
      size_t sent = server.streamFile(file, contentType);
      // Fermer le fichier
      file.close();

      // Valider l'envoi de fichier
      Serial.println(String("Fichier envoyé au client: ") + path);
      return true;
    }

    // Si le fichier n'éxiste pas, renvoyer l'erreur
    Serial.println(String("\tFichier non trouvé : ") + path);
    return false;
  }
/**/

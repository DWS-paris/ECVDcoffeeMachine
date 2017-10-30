# ECV Digital "The Hacked Coffee Machine
Ce repo présente un projet réalisé en collaboration entre [Anthonny Baillard](https://www.linkedin.com/in/anthonybaillard/), [Damien Truffaut](https://www.linkedin.com/in/damient75/) et [Julien Noyer](https://www.linkedin.com/in/julien-noyer-21219b28/) à l'occasion du Hackathon organisé par l'[ECV Digital Paris](http://www.ecvdigital.fr/) les 26 et 27 octobre 2017. Ce projet est un exemple de mise en place d'interactions entre un serveur WeMos D1 R2 et un distributeur de café.

Pour utiliser ce repo vous devez pocéder un microcontrôleur disposant d'une puce [ESP8266](https://fr.wikipedia.org/wiki/ESP8266) comme la [Wemos D1 R2](https://hackspark.fr/fr/wemos-d1-esp8266-arduino-compatible-layout-wifi-80-160mhz-4mb-flash.html) ou la [ESP-WROOM-32](https://hackspark.fr/fr/esp-32-devkitc-esp32-esp-wroom-32.html) qui dispose également d'une connexion bluetooth.

<br>

## Installer le driver de la carte WeMos D1 R2
Si vous possédez une [Wemos D1 R2](https://hackspark.fr/fr/wemos-d1-esp8266-arduino-compatible-layout-wifi-80-160mhz-4mb-flash.html), vous devez installer les drivers nécessaires pour faire fonctionner la carte sur votre odinateur. La [Wemos D1 R2](https://hackspark.fr/fr/wemos-d1-esp8266-arduino-compatible-layout-wifi-80-160mhz-4mb-flash.html) est un modèle de microcontrôlleur récent, il est possible que la configuration ne soit pas possible sur votre ordinateur, si c'est le cas, optez pour une [ESP-WROOM-32](https://hackspark.fr/fr/esp-32-devkitc-esp32-esp-wroom-32.html) qui est plus simple à configurer.

Liens pour télécharger les drivers : 
- [Windows](https://wiki.wemos.cc/_media/file:ch341ser_win.zip)
- [Mac OSX](https://wiki.wemos.cc/_media/ch341ser_mac-1.4.zip)

<br>

## Configuration de l'IDE Ardiuno
Une fois la driver de votre carte installé, vous devez configurer l'[IDE Arduino](https://www.arduino.cc/en/Main/Software) pour qu'il intègre le gestionnaires de la puce [ESP8266](https://fr.wikipedia.org/wiki/ESP8266). Ouvrez votre [IDE Arduino](https://www.arduino.cc/en/Main/Software), sélectionnez l'option "Préférences" et rentrez l'adresse suivante dans le gestionnaire de cartes supplémentaires :
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

L'installation de cette bibliothèque vous permettra de sélectionner votre modèle de carte dans votre [IDE Arduino](https://www.arduino.cc/en/Main/Software). 

<br>

## Editer le projet
Une fois votre carte sélectionnée, vous pouvez ouvrir le fichier [WEMOSwebServer.ino](https://github.com/DWS-paris/ECVDcoffeeMachine/blob/master/WEMOSwebServer.ino) pour modifier les identifiants WiFi : 
```.ino
// Access Point
const char *ssid = "xxx";
const char *password = "xxx";

// Réseau Wifi
const char *ssidWifi = "XXX";
const char *passwordWifi = "XXX";
```

Une fois votre sketch téléversé vous pouvez ouvrir le moniteur série pour y voir l'activité de la carte.
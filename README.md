# ECV Digital "The Hacked Coffee Machine
Ce repo présente un projet réalisé en collaboration entre [Anthonny Baillard](https://www.linkedin.com/in/anthonybaillard/), [Damien Truffaut](https://www.linkedin.com/in/damient75/) et [Julien Noyer](https://www.linkedin.com/in/julien-noyer-21219b28/) à l'occasion du Hackathon organisé par l'[ECV Digital Paris](http://www.ecvdigital.fr/) les 26 et 27 octobre 2017. Ce projet est un exemple de mise en place d'interactions entre un serveur WeMos D1 R2 et un distributeur de café.
<br><br>
Pour utiliser ce repo vous devez pocéder un microcontrôleur disposant d'une puce [ESP8266](https://fr.wikipedia.org/wiki/ESP8266) comme la [Wemos D1 R2](https://hackspark.fr/fr/wemos-d1-esp8266-arduino-compatible-layout-wifi-80-160mhz-4mb-flash.html) ou la [ESP-WROOM-32](https://hackspark.fr/fr/esp-32-devkitc-esp32-esp-wroom-32.html) qui dispose également d'une connexion bluetooth.

## Configuration de l'IDE Ardiuno
Si vous possédez une [Wemos D1 R2](https://hackspark.fr/fr/wemos-d1-esp8266-arduino-compatible-layout-wifi-80-160mhz-4mb-flash.html), vous devez installer les drivers nécessaires pour faire fonctionner la carte sur votre odinateur. La [Wemos D1 R2](https://hackspark.fr/fr/wemos-d1-esp8266-arduino-compatible-layout-wifi-80-160mhz-4mb-flash.html) est un modèle de microcontrôlleur récent, il est possible que la configuration ne soit pas possible sur votre ordinateur, si c'est le cas, optez pour une [ESP-WROOM-32](https://hackspark.fr/fr/esp-32-devkitc-esp32-esp-wroom-32.html) qui est plus simple à configurer.
<br><br>
Liens pour télécharger les drivers : 
- [Windows](https://wiki.wemos.cc/_media/file:ch341ser_win.zip)
- [Mac OSX](https://wiki.wemos.cc/_media/ch341ser_mac-1.4.zip)
<br>
Une fois la driver de votre carte installé, vous devez configurer l'[IDE Arduino](https://www.arduino.cc/en/Main/Software) pour qu'il intègre le gestionnaires de la puce [ESP8266](https://fr.wikipedia.org/wiki/ESP8266). Ouvrez votre [IDE Arduino](https://www.arduino.cc/en/Main/Software), sélectionnez l'option "Préférences" et rentrez l'adresse suivante dans le gestionnaire de cartes supplémentaires :

<br>
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```
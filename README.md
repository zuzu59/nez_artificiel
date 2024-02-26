# nez_artificiel
Création d'un petit nez artificiel *low cost* pour sentir pleins de trucs intéressants ;-)

zf240226.1240


## Buts
Création d'un petit nez artificiel *low cost* pour sentir pleins de trucs intéressants comme par exemple des états de fermentations.

Dans un premier temps on va commencer simple et voir si on arrive à mesurer l'état de cuisson des oignons dans une poêle !<br>
Car c'est un moyen facile et surtout rapide de créer beaucoup de données avec cinq états pour la machine learning:

* air ambiant
* oignons crus
* oignons pas assez cuit (blanchis)
* oignons bien cuit (caramélisé)
* oignons trop cuit (brûlés)


## Problématiques
Mesurer des odeurs au moyen de différents capteurs de gaz  n'est pas facile, car les détecteurs de gaz à oxydes, ceux qui sont justement bon marchés, ne sont pas précis pour mesurer une valeur quantitative, ils dérivent trop d'un senseur à l'autre et aussi au niveau du temps et de la température.

Je vais utiliser un petit coup de pouce de l'IA pour pallier les défauts de ces capteurs.

Mais comme je n'ai pas envie d'être connecté en permanence à Internet pour avoir accès à une Intelligence Artificielle dans le Cloud, on va essayer de le faire directement dans le microcontrôleur à l'aide de TinyML


## Moyens
### Senseurs de gaz
J'ai utilisé le **sensor multichannel gas V2** de Seestudio:

https://wiki.seeedstudio.com/Grove-Multichannel-Gas-Sensor-V2/

![](https://raw.githubusercontent.com/zuzu59/nez_artificiel/master/images/sensor_multichannels.jpg)


Il est vraiment tout petit et le ventilateur est aussi mignon.<br>
Il ne coûte pas trop cher, environ 25CHF !

Senseur de gas:<br>
https://www.reichelt.com/ch/fr/arduino-capteur-de-gaz-multicanal-grove-v2-grv-gas-sens-v2-p328573.html

Ventilateur:<br>
https://www.reichelt.com/ch/fr/raspberry-pi-ventilateur-double-rpi-fan-dual-p223618.html?&trstct=pos_1&nbc=1


### Microcontrôleur
J'ai utilisé pour ce projet le nouveau mini ESP32-C3 de Lolin:

https://www.wemos.cc/en/latest/c3/c3_mini.html

![](https://raw.githubusercontent.com/zuzu59/nez_artificiel/master/images/mini_esp32_c3.png)

Il est petit mais très puissant (CPU RISCV) et pas cher < 4CHF:

https://www.aliexpress.com/item/1005004740051202.html



### Machine Learning
Comme je veux faire de l'IA *embarquée* je vais utiliser la bibliothèque **TensorFlow Lite TinyML for ESP32** !

https://eloquentarduino.com/posts/tensorflow-lite-tinyml-esp32

Mais avant je dois encore lire cet excellent livre sur tinyML:

![](https://raw.githubusercontent.com/zuzu59/nez_artificiel/master/images/livre_tinyml.png)

Avec ce livre, l'IA est démystifiée !

https://books.google.ch/books?id=tn3EDwAAQBAJ&printsec=copyright&redir_esc=y#v=onepage&q&f=false


## Les différents exemples de ce projet
### esp32c3_serial_plot1
Lecture, avec un mini esp32-c3, du senseur multicanaux et le graphe sur le *Serial Plotter Tool* de l'ARDUINO IDE. C'est cette exemple qui a permit d'avoir le résultat du tout 1er prototype

https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-serial-plotter/


### esp32c3_ddplotter1
**---------------- ne fonctionne pas encore ! ----------------**

Lecture, avec un mini esp32-c3, du senseur multicanaux et le graphe sur le smartphone à l'aide de la lib *PlotterDDLayer* de DumbDisplay

https://github.com/trevorwslee/Arduino-DumbDisplay

https://trevorwslee.github.io/ArduinoDumbDisplay/html/class_plotter_d_d_layer.html


### esp32c3_serial_learning1
**---------------- ne fonctionne pas encore ! ----------------**

Lecture, avec un mini esp32-c3, du senseur multicanaux et formate la sortie série pour pouvoir l'utiliser avec Edge Impulse pour l'apprentissage de la machine learning

https://docs.edgeimpulse.com/docs/tools/edge-impulse-cli/cli-daemon


## Résultats du tout 1er prototype
Premier prototype hyper low cost. Le senseur multicanaux et le ventilateur sont *emballés* dans une gaine thermo qui fait office de tunnel d'aspiration. C'est vraiment tout petit !


![](https://raw.githubusercontent.com/zuzu59/nez_artificiel/master/images/nez_artificiel_proto1.jpg)

Détail du proto nez low cost

![](https://raw.githubusercontent.com/zuzu59/nez_artificiel/master/images/nez_artificiel_proto2.jpg)

![](https://raw.githubusercontent.com/zuzu59/nez_artificiel/master/images/nez_artificiel_proto3.jpg)

Pannels de tests, trois *senteurs*, pour *voir* leur *signature* sur un graphique

![](https://raw.githubusercontent.com/zuzu59/nez_artificiel/master/images/trois_senteurs.jpg)

Graphique des *signatures* des *trois senteurs*

![](https://raw.githubusercontent.com/zuzu59/nez_artificiel/master/images/signature_cafe_alcool1.png)

Mais les mesures ont été faites beaucoup trop rapidement et surtout les trois verres étaient côte à côte. Dans la pièce on *sentait* l'odeur du café au whisky ;-)

Ces 4 gaz ont été mesuré

![](https://raw.githubusercontent.com/zuzu59/nez_artificiel/master/images/4_gaz_mesures.png)






## Sources
https://wiki.seeedstudio.com/Grove-Multichannel-Gas-Sensor-V2/

https://github.com/Seeed-Studio/Seeed_Arduino_MultiGas/blob/master/examples/demo_background_gas_name/demo_background_gas_name.ino






.


# nez_artificiel
Création d'un petit nez artificiel *low cost* pour sentir pleins de trucs intéressants ;-)

zf240225.2011


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

xxx


### Microcontrôleur

xxx


### Machine Learning

xxx


## Résultats du tout 1er prototype
Premier prototype hyper low cost. Le senseur multicanaux et le ventilateur sont *emballés* dans une gaine thermo qui fait office de tunnel d'aspiration. C'est vraiment tout petit !


![](https://raw.githubusercontent.com/zuzu59/nez_artificiel/e0519e70b1876770430d03c34a8e4636a138b34e/images/nez_artificiel_proto1.jpg)

Détail du proto nez low cost

![](https://raw.githubusercontent.com/zuzu59/nez_artificiel/e0519e70b1876770430d03c34a8e4636a138b34e/images/nez_artificiel_proto2.jpg)

![](https://raw.githubusercontent.com/zuzu59/nez_artificiel/e0519e70b1876770430d03c34a8e4636a138b34e/images/nez_artificiel_proto3.jpg)

Pannels de tests, trois *senteurs*, pour *voir* leur *signature* sur un graphique

![](https://raw.githubusercontent.com/zuzu59/nez_artificiel/e0519e70b1876770430d03c34a8e4636a138b34e/images/trois_senteurs.jpg)

Graphique des *signatures* des *trois senteurs*

![](https://raw.githubusercontent.com/zuzu59/nez_artificiel/e0519e70b1876770430d03c34a8e4636a138b34e/images/signature_cafe_alcool1.png)

Mais les mesures ont été faites beaucoup trop rapidement et surtout les trois verres étaient côte à côte. Dans la pièce on *sentait* l'odeur du café au whisky ;-)

Ces 4 gaz ont été mesuré

![](https://raw.githubusercontent.com/zuzu59/nez_artificiel/e0519e70b1876770430d03c34a8e4636a138b34e/images/4_gaz_mesures.png)






## Sources





.


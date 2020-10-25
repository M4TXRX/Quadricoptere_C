## Table of contents
* [General info](#general-info)
* [Setup](#setup)

## General info 

LE PRINCIPAL INTERET DE CE PROJET EST D'ANALYSER LE CODE DEVELOPPE POUR LA STABILISATION D'UN QUADRICOPTERE EN VOL. L'UTILISATION D'UNE CENTRALE INERTIELLE MTi-10-series NORMALEMENT UTILISE DANS LE MILIEU AERONOTIQUE PROFESSIONNEL REND D'AUTANT PLUS CE PROJET INTERESSANT.

Ce projet tutoré en groupe de quatre était dans le cadre de notre dernière année d'IUT GEII. Nous y avons consacré un total de 94h00 :
Le projet quadricoptère est un projet qui a consisté à concevoir et à programmer un quadricoptère télécommandé en C (sur la plateforme __AVR Studio__). Ce projet qui avait été commencé en 2011 par d'anciens étudiants, nous aura permis de travailler sur plusieurs domaines qui sont l’électronique, l’automatique ou encore l’informatique industrielle.
Notre objectif était de faire voler le quadricoptère de façon stable.

Durant ce projet nous avons dû dans un premier temps réaliser la __carte d'interface RS232__ pour permettre à notre centrale inertielle __MTi10-series__ de dialoguer avec notre microcontrôleurs (__ATMEGA 1280__).

Puis, il a fallu traiter dans notre programme les données reçues par la centrale inertielle pour réaliser un premier asservissement en angle puis un deuxième en vitesse angulaire. Je me suis personnellement occupé de la partie programmation en C du projet.

Après de nombreuses difficultés rencontrées et surmontées nous avons été le premier groupe depuis 2011 à être parvenu à ce que le quadricoptère vole de façon stable.

Tous les détails du projet sont disponibles dans "Rapport_projet.pdf".

Vidéo de démo du quadricoptère : https://www.youtube.com/watch?v=TGFyJ7FYfgc

	
## Setup

_Les conseils qui vont être donnés ici sont succins, il convient d'avoir de bonnes connaissances en informatique et en électronique, et de bien avoir analysé le rapport du projet et son code avant de le reprendre. En outre, les mesures du Roll, Pitch et Yaw étant faites avec une centrale inertielle MTi10-series qui coute plusieurs miliers d'euros (car très précis), cela rend difficile la reprise de ce projet si c'est pour le loisir. Je vous conseille si c'est le cas de vous tourner vers des projets utilisant un accéléromètre 3 axes et un gyroscope._

Téléchargez le dossier "Carte_RS232.zip" :

* Ouvrez ce dossier contenant les plans de la carte d'interface pour pouvoir la reproduire.

Allez dans le répertoire "Code_C_AVRStudio/Code_C_quadricoptere_termine/" :

* Ouvrez le projet dans AVR studio et téléversez le code compilé sur le microcontroleur ATMEGA 1280.

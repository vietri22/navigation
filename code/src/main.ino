/*
Projet: Le nom du script
Equipe: Votre numero d'equipe
Auteurs: Les membres auteurs du script
Description: Breve description du script
Date: Derniere date de modification
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */
#include <Arduino.h>
#include <LibRobus.h> // Essentielle pour utiliser RobUS
#include <SharpIR.h>
#include <move.h>
#include <stdio.h>
#include <math.h>
#include <ADJDS311.h>
#include <PID.h>
/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces
void suivre();

int checkline(){
  int gauche_3=analogRead(A7), gauche_2=analogRead(A6), gauche_1=analogRead(A5), gauche_0=analogRead(A4);
  int droite_3=analogRead(A0), droite_2=analogRead(A1), droite_1=analogRead(A2), droite_0=analogRead(A3);
  if(gauche_0<500 || droite_0<500){
    return 0;
  }
  else {
    MOTOR_SetSpeed(0,0.2);
}
}


/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */
void suivre()
{
  Serial.println("rentre capteur");
  PID_capteur();
  //Serial.println("rentre decel");
  //Deceleration();
}
/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup(){
  BoardInit();
}


/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop() {
  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
  delay(10);// Delais pour décharger le CPU
  Serial.println(SONAR_GetRange(0));
  PID_capteur();
  delay(1000);
    //suivre();
}
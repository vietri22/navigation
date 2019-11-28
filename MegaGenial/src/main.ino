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
/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */
void suivre()
{
  Serial.println("rentre capteur");
  PID_capteur(5);
  //Serial.println("rentre decel");
  //Deceleration();
}
void cherche(int targetIndex,int direction){
  int angle=0;
  lineCount(targetIndex);
  Serial.println("turnangle");
  avancePID(7);
  if (direction==0)
  {
    angle=-90;
  }
  else
  {
    angle=90;
  }
  turnAngle(angle);
  PID_capteur(11);
  avancePID(7);
  delay(1000);
  //insert bras code
  reculePID(10);
  turnAngle(180);
  lineCount(1);
  avancePID(7);
  turnAngle(-angle);
  lineCount(targetIndex-1);
  PID_capteur(11);
  avancePID(7);
  delay(1000);
  //insert bras code
  reculePID(7);
  turnAngle(180);
  delay(1000);
}
void replace(){
  
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
 //if(Serial3.available())
 // Serial.println(Serial3.read());
 // MOTOR_SetSpeed(0,-0.2);
 // Serial.println(SONAR_GetRange(0));
 // delay(1000);
  if(ROBUS_IsBumper(1)==1){
  Serial.println(SONAR_GetRange(0));
  delay(1000);
  cherche(3,0);
  delay(6000);
  }
}
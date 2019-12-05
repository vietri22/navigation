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
int start = 9;
int direction = 8;
//a5 = blanc= pwm = arret ou marche si high ou low
//a4 = jaune = dir = low ou high = horaire ou antihoraire
/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces
/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */
void get(){
  int i=0;
 while(ROBUS_IsBumper(0)==0 && i<4)
  {
    
    analogWrite(start, 150);
    digitalWrite(direction, LOW);
    MOTOR_SetSpeed(0,0.1);
    MOTOR_SetSpeed(1,0.1);
    delay(250);
    MOTOR_SetSpeed(0,0);
    MOTOR_SetSpeed(1,0);
    delay(2000);
    i++;
  }
  analogWrite(start,0);
  
}
void get1(){
 while(ROBUS_IsBumper(0)==0)
  {
    analogWrite(start, 150);
    digitalWrite(direction, LOW);
  }
  analogWrite(start,0);
}
void giveBack(){
  analogWrite(start,150);
  digitalWrite(direction, HIGH);
  delay(2000);
  analogWrite(start,0);
}
void suivre()
{
  Serial.println("rentre capteur");
  PID_capteur(5);
  //Serial.println("rentre decel");
  //Deceleration();
}
void cherche(int targetIndex,int direction1){
  int angle=0;
  int distanceAvance=3;
  int distanceCapteur=10;
  lineCount(targetIndex);
  Serial.println("turnangle");
  avancePID(7);
  if (direction1==0)
  {
    angle=-90;
  }
  else
  {
    angle=90;
  }
  turnAngle(angle);
  PID_capteur(distanceCapteur);
  avancePID(distanceAvance);
  delay(1000);
  get();
  reculePID(distanceAvance+3);
  turnAngle(180);
  lineCount(1);
  avancePID(7);
  turnAngle(-angle);
  lineCount(targetIndex-1);
  PID_capteur(distanceCapteur);
  avancePID(distanceAvance);
  delay(1000);
  giveBack();
  reculePID(distanceAvance+3);
  turnAngle(180);
  delay(1000);
}
void replace(int targetIndex,int direction1){
  int angle=0;
  int distanceAvance=10;
  int distanceCapteur=15;
  get1();
  lineCount(targetIndex);
  Serial.println("turnangle");
  avancePID(7);
  if (direction1==0)
  {
    angle=-90;
  }
  else
  {
    angle=90;
  }
  turnAngle(angle);
  PID_capteur(distanceCapteur);
  avancePID(distanceAvance);
  delay(1000);
  giveBack();
  reculePID(distanceAvance+3);
  turnAngle(180);
  lineCount(1);
  avancePID(7);
  turnAngle(-angle);
  lineCount(targetIndex-1);
  PID_capteur(distanceCapteur);
  avancePID(distanceAvance);
  delay(1000);
  reculePID(distanceAvance+3);
  turnAngle(180);
  delay(1000);
}
int parseChar(char c){
   return c - 48;
}

int parseInt(char nombre[]){
    int ctr=0;
    int base = 1;
    int convertion=0;
    while (nombre[ctr] !='0')
    {
      convertion+= parseChar(nombre[ctr])*base;
      base*=10;
      ctr++;
    }
  return convertion;
}

void task(int sortie[]){
  char c ='0';
  char ligne ='0';
  char cote = '0';
  char tab[3];
  while(true){
    Serial3.println("n");
    delay(500);
    while (!Serial3.available()){
      delay(10);
    }
    c = Serial3.read();
    //Serial.println(c);
    if(c != 'F'){ 
      int ctr=0;
      tab[0]= c;
      ctr++;
      while(Serial3.available() && ctr < 3 ){
        tab[ctr] = Serial3.read();
        ctr++;
      }  
      Serial.println(tab[0]);
      Serial.println(tab[1]);
      sortie[0] = parseChar(tab[0]);
      sortie[1] = parseChar(tab[1]);
      sortie[2] = parseChar(tab[2]);
      return;
    }
    else{
      delay(1000);
    }
  }
}

/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup(){
  BoardInit();
  Serial3.begin(9600);
  pinMode (start,OUTPUT);
  pinMode (direction,OUTPUT);
}


/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop() {
  int entree[3];
  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
  delay(10);// Delais pour décharger le CPU
 //if(Serial3.available())
 // Serial.println(Serial3.read());
 // MOTOR_SetSpeed(0,-0.2);
 // Serial.println(SONAR_GetRange(0));
 // delay(1000);
  task(entree);
  if (entree[2]==0){
  cherche(entree[0],entree[1]);
  }
  else{
  replace(entree[0],entree[1]);  
  }
  delay(2000);
  }
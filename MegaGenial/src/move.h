#ifndef MOVE_H
#define MOVE_H
/*
fonction : faire tourner le robot à des multiple de 45 degré
entrer :  multiple de 45 degré positif pour tourner vers la droite négatif vers la gauche
sortie : rien
*/
void turn(int mult45);

/*
fonction : faire avencer le robot en ligne droite jusqu'à la distance voulut
entrer :  la distance à parcourir en centimètre
sortie : rien
*/
void avancePID(int distance);

/*
fonction: tourner a des multiples de 1 degre
entrer : angle
sortie: rien
*/
void turnAngle(int angle);
void reculePID(int distance);
#endif
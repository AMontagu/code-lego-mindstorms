#pragma config(Sensor, S1,     capteurContact, sensorTouch)
#pragma config(Sensor, S2,     capteurUltrason,    sensorSONAR)
#pragma config(Sensor, S3,     capteurCouleur,        sensorColorNxtFULL)


void avancer(int tour);
void reculer(int tour);
void tournerGauche(int nombreTour);
void tournerDroite(int nombreTour);
void avancerDroite(int nombreTour);
void avancerGauche(int nombreTour);
void reculerGauche(int nombreTour);
void reculerDroite(int nombreTour);
void avancerContact(int tour);
void avancerObstacle(int tour, int distance);
void avancerCouleur();


task main()
{
	avancerObstacle(30000,15);


}

void avancer(int tour)//fonction avancer
{
    nSyncedMotors = synchAB; //on sychronise les deux moteurs, le moteur A dirige
    nSyncedTurnRatio = 100; //On met les deux moteur a la meme vitesse
    nMotorEncoder[motorA] = 0; //On reinitialise l'encodage du moteur
    nMotorEncoderTarget[motorA] = tour; //on definit la valeur envoye en parametre comme la cible  atteindre
    motor[motorA] = 60; //On met la puissance du moteur a 60%

    while(nMotorRunState[motorA] != runStateIdle)//Tant qu'on  pas atteint la cible on laisse le moteur  60%
    {}
    motor[motorA] = 0;//Une fois la cible atteinte on remet le moteur a 0
}

void reculer(int tour)
{
    nSyncedMotors = synchAB;
    nSyncedTurnRatio = 100;
    nMotorEncoder[motorA] = 0;
    nMotorEncoderTarget[motorA] = tour;
    motor[motorA] = -60;
    while(nMotorRunState[motorA] != runStateIdle)
    {}
    motor[motorA] = 0;
}

void avancerDroite(int nombreTour)
{
    nSyncedMotors = synchAB;
    nSyncedTurnRatio = 50;
    nMotorEncoder[motorB] = 0;
    nMotorEncoderTarget[motorB] = nombreTour;
    motor[motorB] = 60;

    while()
    {}
    motor[motorB] = 0;
}

void avancerGauche(int nombreTour)
{
    nSyncedMotors = synchBA;
    nSyncedTurnRatio = 50;
    nMotorEncoder[motorB] = 0;
    nMotorEncoderTarget[motorB] = nombreTour;
    motor[motorB] = 60;

    while()
    {}
    motor[motorB] = 0;
}

void reculerGauche(int nombreTour)
{
    nSyncedMotors = synchAB;
    nSyncedTurnRatio = 50;
    nMotorEncoder[motorA] = 0;
    nMotorEncoderTarget[motorA] = nombreTour;
    motor[motorA] = -60;
    while(nMotorRunState[motorA] != runStateIdle)    // While the Touch Sensor is inactive (hasn't been pressed):
    {}
    motor[motorA] = 0;
}

void reculerDroite(int nombreTour)
{
    nSyncedMotors = synchBA;
    nSyncedTurnRatio = 50;
    nMotorEncoder[motorB] = 0;
    nMotorEncoderTarget[motorB] = nombreTour;
    motor[motorB] = -60;
    while(nMotorRunState[motorB] != runStateIdle)    // While the Touch Sensor is inactive (hasn't been pressed):
    {}
    motor[motorB] = 0;
}

void tournerGauche(int nombreTour)
{
    nSyncedMotors = synchAB;
    nSyncedTurnRatio = -100;
    nMotorEncoder[motorA] = 0;
    nMotorEncoderTarget[motorA] = nombreTour;
    motor[motorA] = 60;
    while (nMotorRunState[motorA] != runStateIdle)
    {}
    motor[motorA] = 0;
}

void tournerDroite(int nombreTour)
{
    nSyncedMotors = synchBA;
    nSyncedTurnRatio = -100;
    nMotorEncoder[motorB] = 0;
    nMotorEncoderTarget[motorB] = nombreTour;
    motor[motorB] = 60;
    while (nMotorRunState[motorB] != runStateIdle)
    {}
    motor[motorB] = 0;
}

void avancerContact(int tour)//fonction avancer
{
    int valeurCapteurContact;

    nSyncedMotors = synchAB; //on sychronise les deux moteurs, le moteur A dirige
    nSyncedTurnRatio = 100; //On met les deux moteur a la meme vitesse
    nMotorEncoder[motorA] = 0; //On reinitialise l'encodage du moteur
    nMotorEncoderTarget[motorA] = tour; //on definit la valeur envoye en parametre comme la cible  atteindre
    motor[motorA] = 60; //On met la puissance du moteur a 60%

    valeurCapteurContact = SensorValue(capteurContact);

    while(nMotorRunState[motorA] != runStateIdle && valeurCapteurContact == 0)//Tant qu'on  pas atteint la cible ou que le bouton n'a pas été enfoncé
    {
        valeurCapteurContact = SensorValue(capteurContact);// On est obligé de relire la valeur du capteur en continue pour que la condition de la boucle s'effectue.
        nxtDisplayTextLine(2, "%d", valeurCapteurContact); // Pour une variable de type int
    }
    motor[motorA] = 0;//Une fois la cible atteinte on remet le moteur a 0
}

void avancerObstacle(int tour,int distance)//fonction avancer
{
    int valeurCapteurUltrason;

    nSyncedMotors = synchAB; //on sychronise les deux moteurs, le moteur A dirige
    nSyncedTurnRatio = 100; //On met les deux moteur a la meme vitesse
    nMotorEncoder[motorA] = 0; //On reinitialise l'encodage du moteur
    nMotorEncoderTarget[motorA] = tour; //on definit la valeur envoye en parametre comme la cible  atteindre
    motor[motorA] = 60; //On met la puissance du moteur a 60%

    valeurCapteurUltrason = SensorValue(capteurUltrason);

    while(nMotorRunState[motorA] != runStateIdle && valeurCapteurUltrason > distance)//Tant qu'on  pas atteint la cible ou que la distance est supérieur à celle indiqué
    {
        valeurCapteurUltrason = SensorValue(capteurUltrason);// On est obligé de relire la valeur du capteur en continue pour que la condition de la boucle s'effectue.
    }
    motor[motorA] = 0;//Une fois la cible atteinte on remet le moteur a 0
}

void avancerCouleur(int tour,int distance)//fonction avancer
{
    int valeurCapteurCouleur;
    int valeurCouleurOriginal;

    nSyncedMotors = synchAB; //on sychronise les deux moteurs, le moteur A dirige
    nSyncedTurnRatio = 100; //On met les deux moteur a la meme vitesse
    nMotorEncoder[motorA] = 0; //On reinitialise l'encodage du moteur
    nMotorEncoderTarget[motorA] = tour; //on definit la valeur envoye en parametre comme la cible  atteindre
    motor[motorA] = 60; //On met la puissance du moteur a 60%

    valeurCapteurCouleur = SensorValue(capteurCouleur);
    valeurCouleurOriginal = SensorValue(capteurCouleur);

    while(valeurCapteurCouleur == valeurCouleurOriginal)//Tant qu'on  a pas changé de couleur
    {
        valeurCapteurCouleur = SensorValue(capteurCouleur);// On est obligé de relire la valeur du capteur en continue pour que la condition de la boucle s'effectue.
    }
    motor[motorA] = 0;//Une fois la cible atteinte on remet le moteur a 0
}

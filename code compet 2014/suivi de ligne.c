#pragma config(Sensor, S1,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S2,     capteurTouchGauche, sensorTouch)
#pragma config(Sensor, S3,     capteurTouchDroite, sensorTouch)
#pragma config(Sensor, S4,     couleur,        sensorColorNxtRED)

void tournerGauche(int nombreTour);
void tournerDroite(int nombreTour);
int avancerDroite();
int avancerGauche();
int reculerGauche();
int reculerDroite();
void reculer(int nombreTour);
int avancer(int nombreTour);

task main()
{
	nSyncedMotors = synchAB;
	int valeurCapteurLumiere;
	int positionC = 1; // 0 centre, 1 droite, 2 gauche
	int nombreAvancerSansNoir = 0;// 0 coup d'avant on etait sur noir, 1 coup d'avant on etait pas sur noir
	int nbrChgt = 0;
	int valeurNombreNoir = 6;
	int avancerSinon = 0;
	int avancerOui = 0;
	int trouverNoir = 0;
	while(true)
	{
		valeurCapteurLumiere = SensorValue(couleur);
		if(valeurCapteurLumiere >= 170 && valeurCapteurLumiere <= 460)
		{
			nSyncedMotors = synchAB;
			nSyncedTurnRatio = 100;
			nMotorEncoderTarget[motorA] = 60;
			motor[motorA] = 700;
			while (nMotorRunState[motorA] != runStateIdle)
		 	{}
		 	motor[motorA] = 0;
			nombreAvancerSansNoir = 0;
			nbrChgt = 0;
			valeurNombreNoir = 6;
			avancerSinon = 0;
		}
		else if(valeurCapteurLumiere > 460 && nombreAvancerSansNoir <= valeurNombreNoir && nbrChgt <= 1 && avancerSinon <= 1)
		{
			if(positionC == 1)
			{
	  		tournerGauche(10);
	  	}
	  	else if(positionC == 2)
	  	{
	  		tournerDroite(10);
			}
			nombreAvancerSansNoir++;
			wait1Msec(300);
		}
		else if(valeurCapteurLumiere > 460 && nombreAvancerSansNoir > valeurNombreNoir && nbrChgt <= 1 && avancerSinon <= 1)
		{
			if(positionC == 1)
			{
				if(valeurNombreNoir == 14)
				{
					tournerDroite(140);
				}
				else
				{
					tournerDroite(60);
				}
				positionC = 2;
				nombreAvancerSansNoir = 0;
			}
			else if(positionC == 2)
			{
				if(valeurNombreNoir == 14)
				{
					tournerGauche(120);
				}
				else
				{
					tournerGauche(60);
				}
				positionC = 1;
				nombreAvancerSansNoir = 0;
			}
			nbrChgt++;
		}
		else if(valeurCapteurLumiere > 460 && nbrChgt == 2 && avancerSinon <= 1)
		{
			valeurNombreNoir = 14;
			avancerSinon++;
			nbrChgt = 0;
		}
		else if(valeurCapteurLumiere > 460 && avancerSinon == 2)
		{
			if(avancerOui == 0)
			{
				reculer(200);
				trouverNoir = avancerDroite();
				if(trouverNoir == 0)
				{
					trouverNoir = avancer(600);
				}
				avancerOui = 1;
			}
			else if(avancerOui == 1)
			{
				reculer(300);
				reculerGauche();
				trouverNoir = avancerGauche();
				if(trouverNoir == 0)
				{
					trouverNoir = avancer(600);
				}
				avancerOui = 2;
			}
			if(trouverNoir == 1)
			{
				avancerSinon = 0;
			}
		}
	}
}

void tournerGauche(int nombreTour)
{
	nSyncedMotors = synchAB; //motor A is the master, motor B is the slave
	nSyncedTurnRatio = -100;
	nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = nombreTour; // 280 passer d'un extreme  l'autre donc 140 du milieu  un extreme
	motor[motorA] = 50;
	while (nMotorRunState[motorA] != runStateIdle)
	{}
	motor[motorA] = 0;
}

void tournerDroite(int nombreTour)
{
	nSyncedMotors = synchBA; //motor A is the master, motor B is the slave
	nSyncedTurnRatio = -100;
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = nombreTour; // 280 passer d'un extreme  l'autre donc 140 du milieu  un extreme
	motor[motorB] = 50;
	while (nMotorRunState[motorB] != runStateIdle)
	{}
	motor[motorB] = 0;
}

int avancerDroite()
{
	int valeurCapteurLumiere = 0;
	int sonarValue = 0;
	nSyncedMotors = synchAB; //motor A is the master, motor B is the slave
	nSyncedTurnRatio = 50;
	nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = 300;
	motor[motorA] = 100;
	sonarValue = SensorValue(sonarSensor);
	valeurCapteurLumiere = SensorValue(couleur);
	while(sonarValue > 15 && nMotorRunState[motorA] != runStateIdle && valeurCapteurLumiere > 400)    // While the Touch Sensor is inactive (hasn't been pressed):
	{
		sonarValue = SensorValue(sonarSensor);
		valeurCapteurLumiere = SensorValue(couleur);
	}
	motor[motorA] = 0;
	if(valeurCapteurLumiere >= 170 && valeurCapteurLumiere <=400)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int avancerGauche()
{
	int valeurCapteurLumiere = 0;
	int sonarValue = 0;
	nSyncedMotors = synchBA; //motor A is the master, motor B is the slave
	nSyncedTurnRatio = 50;
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = 200;
	motor[motorB] = 100;
	valeurCapteurLumiere = SensorValue(couleur);
	while(sonarValue > 15 && nMotorRunState[motorB] != runStateIdle && valeurCapteurLumiere > 400)    // While the Touch Sensor is inactive (hasn't been pressed):
  {
  	sonarValue = SensorValue(sonarSensor);
  	valeurCapteurLumiere = SensorValue(couleur);
  }
  motor[motorB] = 0;
  if(valeurCapteurLumiere >= 170 && valeurCapteurLumiere <=400)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int reculerGauche()
{
	int valeurCapteurDroit; // 1023 bouton relacher 183 bouton appuyer
	int valeurCapteurGauche;
	nSyncedMotors = synchAB; //motor A is the master, motor B is the slave
	nSyncedTurnRatio = 50;
	nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = 300;
	motor[motorA] = -100;
	valeurCapteurDroit = SensorValue(capteurTouchDroite);
	valeurCapteurGauche = SensorValue(capteurTouchGauche);
	wait1Msec(200);
	while(valeurCapteurGauche == 1023 && valeurCapteurDroit == 1023 && nMotorRunState[motorA] != runStateIdle)    // While the Touch Sensor is inactive (hasn't been pressed):
  {
  	valeurCapteurDroit = SensorValue(capteurTouchDroite);
	  valeurCapteurGauche = SensorValue(capteurTouchGauche);
  }
  motor[motorA] = 0;
	if(valeurCapteurGauche < 1000)
	{
		return 1;
	}
	else if(valeurCapteurDroit < 1000)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

int reculerDroite()
{
	int valeurCapteurDroit; // 1023 bouton relacher 183 bouton appuyer
	int valeurCapteurGauche;
	nSyncedMotors = synchBA; //motor A is the master, motor B is the slave
	nSyncedTurnRatio = 50;
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = 300;
	motor[motorB] = -100;
	valeurCapteurDroit = SensorValue(capteurTouchDroite);
	valeurCapteurGauche = SensorValue(capteurTouchGauche);
	while(valeurCapteurGauche == 1023 && valeurCapteurDroit == 1023 && nMotorRunState[motorB] != runStateIdle)    // While the Touch Sensor is inactive (hasn't been pressed):
  {
  	valeurCapteurDroit = SensorValue(capteurTouchDroite);
	  valeurCapteurGauche = SensorValue(capteurTouchGauche);
  }
  motor[motorB] = 0;
	if(valeurCapteurGauche < 1000)
	{
		return 1;
	}
	else if(valeurCapteurDroit < 1000)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

void reculer(int nombreTour)
{
	nSyncedMotors = synchAB;
  nSyncedTurnRatio = 100; //motors move in opposite directions of each other
  nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = nombreTour;
	motor[motorA] = -100;
	while(nMotorRunState[motorA] != runStateIdle)    // While the Touch Sensor is inactive (hasn't been pressed):
	{}
	motor[motorA] = 0;
}

int avancer(int nombreTour)
{
	int valeurCapteurLumiere = 0;
	nSyncedMotors = synchAB;
  nSyncedTurnRatio = 100; //motors move in opposite directions of each other
  nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = nombreTour;
	motor[motorA] = 50;
	valeurCapteurLumiere = SensorValue(couleur);
	while(nMotorRunState[motorA] != runStateIdle && valeurCapteurLumiere > 400)    // While the Touch Sensor is inactive (hasn't been pressed):
	{
		valeurCapteurLumiere = SensorValue(couleur);
		wait1Msec(150);
	}
	motor[motorA] = 0;
	if(valeurCapteurLumiere >= 170 && valeurCapteurLumiere <=400)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

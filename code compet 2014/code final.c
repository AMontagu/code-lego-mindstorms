#pragma config(Sensor, S1,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S2,     capteurTouchGauche, sensorTouch)
#pragma config(Sensor, S3,     capteurTouchDroite, sensorTouch)
#pragma config(Sensor, S4,     couleur,        sensorColorNxtFULL)
#pragma config(MotorPidSetting,  motorA,  255, 255, 65535, 255, 255,   65535, 65535, 65535)
#pragma config(MotorPidSetting,  motorB,  255, 255, 65535, 255, 255,   65535, 65535, 65535)
#pragma config(MotorPidSetting,  motorC,  255, 255, 65535, 255, 255,   65535, 65535, 65535)

void avancerObstacle(int distance);
int tournerGauche(int nombreTour);
int tournerDroite(int nombreTour);
int avancerDroite(int nombreTour, int distance);
int avancerGauche(int nombreTour, int distance);
void reculerGauche(int nombreTour);
void reculerDroite(int nombreTour);
void reculer(int nombreTour);
int avancer(int nombreTour, int distance);
void sprint();

int avancerJusqua(int couleurATrouver);
int chercherSortie();

int avancerLigne(int couleurATrouver);
int avancerTest(int passerCouleur);
void avancerEncore(int nombreTour);

void suivreLigne();

task main()
{
	nSyncedMotors = synchAB;
	nSyncedTurnRatio = 100;
	//int positionC = 1; // 0 centre, 1 droite, 2 gauche
	//int nombreAvancerSansNoir = 0;// 0 coup d'avant on etait sur noir, 1 coup d'avant on etait pas sur noir
	int distance = 0;
	//int valeurCapteurLumiere = sensorRaw[couleur];
	int continuer = 1;
	int tailleLigne;
	int testCouleur = 0;
	int dep25 = 330;
	int dep50 =	825;
	int dep100 =	1630;
	int dep150 =	2200;
	int dep200 = 2800;
	int quartG =	168;
	int demiG = 290;
	int fullG = 600;
	int quartD = 140;
	while(continuer == 1)
	{
		//motor[motorA] = 60;
		tailleLigne = chercherSortie();
		if(tailleLigne == 1)
		{
			avancer(4000, 10);
			tournerGauche(quartG);
			avancer(dep50, 10);
			tournerGauche(quartG);
			avancer(dep150, 10);
			testCouleur = avancerJusqua(4);
			if(testCouleur != 0)
			{
				avancer(dep25, 10);
				tournerGauche(fullG);
				playSound(soundLowBuzzShort);
				testCouleur = 0;
			}
			avancer(dep100, 10);
			tournerGauche(quartG);
			avancer(dep100, 10);
			tournerGauche(quartG);
			avancer(dep100, 10);
			tournerDroite(quartD);
			avancer(dep100, 10);
			tournerDroite(quartD);
			testCouleur = avancerJusqua(2);
			if(testCouleur != 0)
			{
				avancer(dep25, 10);
				tournerGauche(demiG);
				reculer(250);
				playSound(soundUpwardTones);
				avancer(400, 10);
				testCouleur = 0;
			}
			tournerGauche(quartG);
			avancer(dep100, 10);
			tournerGauche(quartG);
			avancer(dep100, 10);
		}
		else // code 2 me chemin
		{
			avancer(515, 10);
			tournerDroite(quartD);
			avancer(dep150, 10);
			tournerDroite(quartD);
			avancer(dep50, 10);
			tournerGauche(quartG);
			avancer(dep100, 10);
			tournerDroite(quartD);
			testCouleur = avancerJusqua(2);
			if(testCouleur != 0)
			{
				avancer(700, 10);
				tournerGauche(demiG);
				playSound(soundUpwardTones);
				avancerObstacle(25);
				testCouleur = 0;
			}
			tournerGauche(quartG);
			avancer(dep100, 10);
			tournerGauche(quartG);
			avancer(dep100, 10);
			tournerDroite(quartD);
			avancer(dep100, 10);
			tournerDroite(quartD);
			avancer(dep50, 10);
			testCouleur = avancerJusqua(4);
			if(testCouleur != 0)
			{
				avancer(dep25, 10);
				tournerGauche(fullG);
				tournerGauche(demiG);
				playSound(soundLowBuzzShort);
				testCouleur = 0;
			}
			avancer(dep100, 10);
			tournerGauche(quartG);
			avancer(dep100, 10);
			tournerDroite(quartD);
		}
		testCouleur = avancerJusqua(5);
		if(testCouleur != 0)
		{
			avancer(100, 10);
			suivreLigne();
			testCouleur = 0;
		}
		sprint();
		avancerObstacle(22);
		testCouleur = avancerJusqua(1);
		if(testCouleur != 0)
		{
			avancer(300, 0);
			tournerGauche(quartG);
			avancer(dep25, 0);
			playSound(soundBeepBeep);
			reculer(300);
			avancer(300, 0);
			playSound(soundBeepBeep);
			reculer(300);
			tournerGauche(fullG);
			avancer(300, 0);
			playSound(soundException);
			reculer(300);
			testCouleur = 0;
		}
		tournerDroite(quartD);
		avancerObstacle(30);
		tournerGauche(quartG);
		avancer(dep150, 0);
		tailleLigne = 0;
	}
}

int chercherSortie()
{
	int compteur = 0;
	int compteur2 = 0;
  int sonarValue = 0;
  int trouverLigne = 0;

	int valeurBtnGauche;
  int valeurBtnDroite;

  while(trouverLigne == 0)
  {

		sonarValue = SensorValue(sonarSensor);
		valeurBtnGauche = SensorValue(capteurTouchGauche);
		valeurBtnDroite = SensorValue(capteurTouchDroite);

		while(sonarValue < 45 && valeurBtnGauche == 1023 && valeurBtnDroite == 1023)
		{
			//nxtDisplayCenteredTextLine(1,"%d", sonarValue);
			wait1Msec(800);
			compteur++;
			compteur2 = 0;
			tournerDroite(20);
			if(compteur > 30)
			{
				reculerDroite(100);
				compteur = 0;
			}
			sonarValue = SensorValue(sonarSensor);
			valeurBtnGauche = SensorValue(capteurTouchGauche);
			valeurBtnDroite = SensorValue(capteurTouchDroite);
		}
		if(valeurBtnGauche < 1000)
		{
			reculer(300);
			wait1Msec(200);
			tournerDroite(60);
		}
		else if(valeurBtnDroite < 1000)
		{
			reculer(300);
			wait1Msec(200);
			tournerGauche(60);
		}
		else
		{
			//nxtDisplayCenteredTextLine(7,"dans else");
			if(compteur2 == 0)
			{
				//nxtDisplayCenteredTextLine(2,"dans avancer");
				avancer(450, 10);
				compteur2++;
			}
			else if(compteur2 == 1)
			{
				trouverLigne = avancerJusqua(3);
				compteur2 = 0;
			}
			else
			{
				reculer(200);
				tournerDroite(50);
				compteur2 = 0;
			}
		}
	}
	if(trouverLigne == 1)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

int avancerJusqua(int couleurATrouver)
{
	int valeurCapteurLumiere;
	int doubleLigne = 0;
	int passerCouleur = 6;
	nSyncedMotors = synchAB;
	nSyncedTurnRatio = 100;
	int sonarValue;
	int valeurBtnGauche;
  int valeurBtnDroite;

	while(true)
	{
		sonarValue = SensorValue(sonarSensor);
		valeurBtnGauche = SensorValue(capteurTouchGauche);
		valeurBtnDroite = SensorValue(capteurTouchDroite);
		while(sonarValue > 35 && valeurBtnGauche == 1023 && valeurBtnDroite == 1023 && doubleLigne == 0)
		{
			sonarValue = SensorValue(sonarSensor);
			valeurBtnGauche = SensorValue(capteurTouchGauche);
			valeurBtnDroite = SensorValue(capteurTouchDroite);

			wait1Msec(200);
			valeurCapteurLumiere = SensorValue(couleur);
			wait1Msec(200);
			if(valeurCapteurLumiere != couleurATrouver && passerCouleur != couleurATrouver)
			{
				passerCouleur = avancerLigne(couleurATrouver);
			}
			else
			{
				doubleLigne = avancerTest(passerCouleur);
				passerCouleur = 6;
			}
			if(doubleLigne != 0)
			{
				if(doubleLigne == 1)
				{
					playSound(soundBlip);
					wait1Msec(1000);
					playSound(soundBlip);
					wait1Msec(1000);
					playSound(soundBlip);
					return 2;
				}
				else
				{
					playSound(soundDownwardTones);
					return 1;
				}
				doubleLigne = 0;
			}
		}
		if(valeurBtnGauche < 1000)
		{
			reculer(300);
			wait1Msec(200);
			tournerDroite(70);
		}
		else if(valeurBtnDroite < 1000)
		{
			reculer(300);
			wait1Msec(200);
			tournerGauche(70);
		}
		else if(sonarValue < 35)
		{
			reculer(300);
			wait1Msec(200);
			tournerDroite(70);
		}
		sonarValue = SensorValue(sonarSensor);
		valeurBtnGauche = SensorValue(capteurTouchGauche);
		valeurBtnDroite = SensorValue(capteurTouchDroite);
	}
}

int avancerLigne(int couleurATrouver)
{
	int valeurCapteurLumiere = 0;
	nSyncedMotors = synchAB;
  nSyncedTurnRatio = 100; //motors move in opposite directions of each other
  nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = 19;
	motor[motorA] = 20;
	valeurCapteurLumiere = SensorValue(couleur);
	while(nMotorRunState[motorA] != runStateIdle && valeurCapteurLumiere != couleurATrouver)    // While the Touch Sensor is inactive (hasn't been pressed):
	{
		valeurCapteurLumiere = SensorValue(couleur);
	}
	motor[motorA] = 0;
	return valeurCapteurLumiere;
}

int avancerTest(int passerCouleur)
{
	int valeurCapteurLumiere = 0;
	nSyncedMotors = synchAB;
  nSyncedTurnRatio = 100; //motors move in opposite directions of each other
  nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = 40;
	motor[motorA] = 30;
	while(nMotorRunState[motorA] != runStateIdle)    // While the Touch Sensor is inactive (hasn't been pressed):
	{}
	motor[motorA] = 0;

	wait1Msec(500);
	valeurCapteurLumiere = SensorValue(couleur);

	if(valeurCapteurLumiere == passerCouleur)
	{
		return 1;
	}
	else
	{
	  avancerEncore(13);

		wait1Msec(1000);
		valeurCapteurLumiere = SensorValue(couleur);

		if(valeurCapteurLumiere == passerCouleur)
		{
			return 1;
		}
		else
		{
			avancerEncore(13);

			wait1Msec(1000);
			valeurCapteurLumiere = SensorValue(couleur);

			if(valeurCapteurLumiere == passerCouleur)
			{
				return 1;
			}
			else
			{
				avancerEncore(13);

				wait1Msec(1000);
				valeurCapteurLumiere = SensorValue(couleur);

				if(valeurCapteurLumiere == passerCouleur)
				{
					return 1;
				}
				else
				{
					return 2;
				}
			}
		}
	}
}

void avancerEncore(int nombreTour)
{
	nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = nombreTour;
	motor[motorA] = 30;
	while(nMotorRunState[motorA] != runStateIdle)    // While the Touch Sensor is inactive (hasn't been pressed):
	{}
	motor[motorA] = 0;
}

void avancerObstacle(int distance)
{
	nSyncedMotors = synchAB;
  nSyncedTurnRatio = 100;
	int speed = 0;
  int sonarValue = 0;
  int valeurBtnGauche;
  int valeurBtnDroite;

	sonarValue = SensorValue(sonarSensor);
	valeurBtnGauche = SensorValue(capteurTouchGauche);
	valeurBtnDroite = SensorValue(capteurTouchDroite);

	while(sonarValue > distance && valeurBtnGauche == 1023 && valeurBtnDroite == 1023)
	{
		wait1Msec(100);
		speed = (SensorValue(sonarSensor) - 10);
		if(speed > 40)
		{
			speed = 100;
		}
		motor[motorA] = speed;
		sonarValue = SensorValue(sonarSensor);
		valeurBtnGauche = SensorValue(capteurTouchGauche);
		valeurBtnDroite = SensorValue(capteurTouchDroite);
	}
	motor[motorA] = 0;
	if(valeurBtnGauche < 1000)
	{
		reculer(300);
		wait1Msec(200);
		//avancerObstacle(25);
		avancer(200, 10);
	}
	else if(valeurBtnDroite < 1000)
	{
		reculer(300);
		wait1Msec(200);
		//avancerObstacle(25);
		avancer(200, 10);
	}
	tournerGauche(290);
	sonarValue = SensorValue(sonarSensor);
	valeurBtnGauche = SensorValue(capteurTouchGauche);
	valeurBtnDroite = SensorValue(capteurTouchDroite);
}

int avancer(int nombreTour, int distance)
{
	nSyncedMotors = synchAB;
  nSyncedTurnRatio = 100;
  nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = nombreTour;
	motor[motorA] = 60;

	int sonarValue;
	int valeurBtnGauche;
  int valeurBtnDroite;

	sonarValue = SensorValue(sonarSensor);
	valeurBtnGauche = SensorValue(capteurTouchGauche);
	valeurBtnDroite = SensorValue(capteurTouchDroite);

	while(nMotorRunState[motorA] != runStateIdle && valeurBtnGauche == 1023 && valeurBtnDroite == 1023 && sonarValue > distance)
	{
		sonarValue = SensorValue(sonarSensor);
		valeurBtnGauche = SensorValue(capteurTouchGauche);
		valeurBtnDroite = SensorValue(capteurTouchDroite);
		wait1Msec(300);
	}
	motor[motorA] = 0;
	if(valeurBtnGauche < 1000)
	{
		reculer(300);
		wait1Msec(200);
		tournerDroite(70);
		//avancerObstacle(25);
		avancer(200, 10);
	}
	else if(valeurBtnDroite < 1000)
	{
		reculer(300);
		wait1Msec(200);
		tournerGauche(70);
		//avancerObstacle(25);
		avancer(200, 10);
	}
	else if(sonarValue < distance)
	{
		reculer(300);
		wait1Msec(200);
		tournerDroite(70);
	}
	sonarValue = SensorValue(sonarSensor);
	valeurBtnGauche = SensorValue(capteurTouchGauche);
	valeurBtnDroite = SensorValue(capteurTouchDroite);
	return 1;
}

void reculer(int nombreTour)
{
	nSyncedMotors = synchAB;
  nSyncedTurnRatio = 100;
  nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = nombreTour;
	motor[motorA] = -60;
	while(nMotorRunState[motorA] != runStateIdle)
	{}
	motor[motorA] = 0;
}

int avancerDroite(int nombreTour, int distance)
{
	int sonarValue = 0;
	nSyncedMotors = synchAB;
	nSyncedTurnRatio = 50;
	nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = nombreTour;
	motor[motorA] = 60;

	int valeurBtnGauche;
  int valeurBtnDroite;

	valeurBtnGauche = SensorValue(capteurTouchGauche);
	valeurBtnDroite = SensorValue(capteurTouchDroite);
	sonarValue = SensorValue(sonarSensor);
	while(sonarValue > distance && nMotorRunState[motorA] != runStateIdle && valeurBtnGauche == 1023 && valeurBtnDroite == 1023)
	{
		sonarValue = SensorValue(sonarSensor);
	}
	motor[motorA] = 0;
	if(valeurBtnGauche < 1000)
	{
		reculer(300);
		wait1Msec(200);
		tournerDroite(70);
		//avancerObstacle(25);
		avancer(200, 10);
	}
	else if(valeurBtnDroite < 1000)
	{
		reculer(300);
		wait1Msec(200);
		tournerGauche(70);
		//avancerObstacle(25);
		avancer(200, 10);
	}
	else if(sonarValue < distance)
	{
		reculer(300);
		wait1Msec(200);
		tournerDroite(70);
	}
	return 1;
}

int avancerGauche(int nombreTour, int distance)
{
	int sonarValue = 0;
	nSyncedMotors = synchBA;
	nSyncedTurnRatio = 50;
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = nombreTour;
	motor[motorB] = 60;

	int valeurBtnGauche;
  int valeurBtnDroite;

	valeurBtnGauche = SensorValue(capteurTouchGauche);
	valeurBtnDroite = SensorValue(capteurTouchDroite);
	sonarValue = SensorValue(sonarSensor);

	while(sonarValue > distance && nMotorRunState[motorB] != runStateIdle && valeurBtnGauche == 1023 && valeurBtnDroite == 1023)
  {
  	sonarValue = SensorValue(sonarSensor);
  	valeurBtnGauche = SensorValue(capteurTouchGauche);
		valeurBtnDroite = SensorValue(capteurTouchDroite);
  }
  motor[motorB] = 0;
 	if(valeurBtnGauche < 1000)
	{
		reculer(300);
		wait1Msec(200);
		tournerDroite(70);
		//avancerObstacle(25);
		avancer(200, 10);
	}
	else if(valeurBtnDroite < 1000)
	{
		reculer(300);
		wait1Msec(200);
		tournerGauche(70);
		//avancerObstacle(25);
		avancer(200, 10);
	}
	else if(sonarValue < distance)
	{
		reculer(300);
		wait1Msec(200);
		tournerDroite(70);
	}
	return 1;
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

int tournerGauche(int nombreTour)
{
	nSyncedMotors = synchAB;
	nSyncedTurnRatio = -100;
	nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = nombreTour;
	motor[motorA] = 60;
	while (nMotorRunState[motorA] != runStateIdle)
	{}
	motor[motorA] = 0;
	return 1;
}

int tournerDroite(int nombreTour)
{
	nSyncedMotors = synchBA;
	nSyncedTurnRatio = -100;
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = nombreTour;
	motor[motorB] = 60;
	while (nMotorRunState[motorB] != runStateIdle)
	{}
	motor[motorB] = 0;
	return 1;
}

void suivreLigne()
{
	nSyncedMotors = synchAB;
	int valeurCapteurLumiere;
	int positionC = 1; // 0 centre, 1 droite, 2 gauche
	int nombreAvancerSansNoir = 0;// 0 coup d'avant on etait sur noir, 1 coup d'avant on etait pas sur noir
	int nbrChgt = 0;
	int valeurNombreNoir = 3;
	int avancerSinon = 0;
	int avancerOui = 0;
	int trouverNoir = 0;
	int compteur = 0;
	while(valeurCapteurLumiere != 5)
	{
		valeurCapteurLumiere = SensorValue(couleur);
		wait1Msec(300);
		if(valeurCapteurLumiere == 1)
		{
			nSyncedMotors = synchAB;
			nSyncedTurnRatio = 100;
			nMotorEncoderTarget[motorA] = 100;
			motor[motorA] = 50;
			while (nMotorRunState[motorA] != runStateIdle)
		 	{}
		 	motor[motorA] = 0;
			nombreAvancerSansNoir = 0;
			nbrChgt = 0;
			valeurNombreNoir = 3;
			avancerSinon = 0;
		}
		else if(valeurCapteurLumiere != 1 && nombreAvancerSansNoir <= valeurNombreNoir && nbrChgt <= 1 && avancerSinon <= 1)
		{
			if(positionC == 1)
			{
	  		tournerGauche(15);
	  	}
	  	else if(positionC == 2)
	  	{
	  		tournerDroite(15);
			}
			nombreAvancerSansNoir++;
		}
		else if(valeurCapteurLumiere != 1 && nombreAvancerSansNoir > valeurNombreNoir && nbrChgt <= 1 && avancerSinon <= 1)
		{
			if(positionC == 1)
			{
				if(valeurNombreNoir == 9)
				{
					tournerDroite(125);
				}
				else
				{
					tournerDroite(45);
				}
				positionC = 2;
				nombreAvancerSansNoir = 0;
			}
			else if(positionC == 2)
			{
				if(valeurNombreNoir == 9)
				{
					tournerGauche(125);
				}
				else
				{
					tournerGauche(45);
				}
				positionC = 1;
				nombreAvancerSansNoir = 0;
			}
			nbrChgt++;
		}
		else if(valeurCapteurLumiere != 1 && nbrChgt == 2 && avancerSinon <= 1)
		{
			valeurNombreNoir = 9;
			avancerSinon++;
			nbrChgt = 0;
		}
		else if(valeurCapteurLumiere != 1 && avancerSinon == 2)
		{
			if(avancerOui == 0)
			{
				trouverNoir = avancerDroite(150, 20);
				if(trouverNoir == 0)
				{
					if(compteur <= 9)
					{
						trouverNoir = avancerLigne(1);
						compteur++;
					}
				}
				if(compteur > 10)
				{
					avancerOui = 1;
				}
			}
			else if(avancerOui == 1)
			{
				reculer(200);
				reculerGauche(80);
				trouverNoir = avancerGauche(150, 20);
				if(trouverNoir == 0)
				{
					if(compteur <= 9)
					{
						trouverNoir = avancerLigne(1);
						compteur++;
					}
				}
				if(compteur > 10)
				{
					avancerOui = 1;
				}
			}
			if(trouverNoir == 1 || trouverNoir == 2)
			{
				avancerSinon = 0;
			}
		}
	}
}

void sprint()
{
	nSyncedMotors = synchAB;
  nSyncedTurnRatio = 100;
  nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = 2150;
	motor[motorA] = 100;

	int sonarValue;
	int valeurBtnGauche;
  int valeurBtnDroite;

	sonarValue = SensorValue(sonarSensor);
	valeurBtnGauche = SensorValue(capteurTouchGauche);
	valeurBtnDroite = SensorValue(capteurTouchDroite);

	while(nMotorRunState[motorA] != runStateIdle && valeurBtnGauche == 1023 && valeurBtnDroite == 1023 && sonarValue > 20)
	{
		sonarValue = SensorValue(sonarSensor);
		valeurBtnGauche = SensorValue(capteurTouchGauche);
		valeurBtnDroite = SensorValue(capteurTouchDroite);
		wait1Msec(300);
	}
	motor[motorA] = 0;
	if(valeurBtnGauche < 1000)
	{
		reculer(300);
		wait1Msec(200);
		tournerDroite(70);
		//avancerObstacle(25);
		avancer(200, 10);
	}
	else if(valeurBtnDroite < 1000)
	{
		reculer(300);
		wait1Msec(200);
		tournerGauche(70);
		//avancerObstacle(25);
		avancer(200, 10);
	}
	else if(sonarValue < 20)
	{
		reculer(300);
		wait1Msec(200);
		tournerDroite(70);
		avancer(200, 10);
	}
}

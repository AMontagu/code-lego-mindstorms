#pragma config(Sensor, S1,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S2,     capteurTouchGauche, sensorTouch)
#pragma config(Sensor, S3,     capteurTouchDroite, sensorTouch)
#pragma config(Sensor, S4,     couleur,        sensorColorNxtRED)
#pragma config(MotorPidSetting,  motorA,  255, 255, 65535, 255, 255,   65535, 65535, 65535)
#pragma config(MotorPidSetting,  motorB,  255, 255, 65535, 255, 255,   65535, 65535, 65535)
#pragma config(MotorPidSetting,  motorC,  255, 255, 65535, 255, 255,   65535, 65535, 65535)

int avancer(int nombreTour);

task main()
{
	int passerVert = 0;
	int passerRouge = 0;
	int passerBleu = 0;
	int passerJaune = 0;
	int passerNoir = 0;
	int passerCouleur = 0;
	int valeurCapteurLumiere = SensorValue(couleur);
	int ancienCaptage = valeurCapteurLumiere;
	nSyncedMotors = synchAB;
	nSyncedTurnRatio = 100;

	while(true)
	{
		if(valeurCapteurLumiere >= ancienCaptage - 40 && valeurCapteurLumiere <= ancienCaptage + 40 && passerCouleur == 0)
		{
			avancer(30);
			ancienCaptage = valeurCapteurLumiere;
			valeurCapteurLumiere = SensorValue(couleur);
			//wait1Msec(200);
		}
		else
		{
			motor[motorA] = 0;
			nxtDisplayCenteredTextLine(7, "%d", valeurCapteurLumiere);
			passerVert = 1;
			wait1Msec(1500);
			valeurCapteurLumiere = SensorValue(couleur);
			ancienCaptage = valeurCapteurLumiere;
		}
	}
}

int avancer(int nombreTour)
{
	int valeurCapteurLumiere = 0;
	nSyncedMotors = synchAB;
  nSyncedTurnRatio = 100; //motors move in opposite directions of each other
  nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = nombreTour;
	motor[motorA] = 70;
	valeurCapteurLumiere = SensorValue(couleur);
	while(nMotorRunState[motorA] != runStateIdle)    // While the Touch Sensor is inactive (hasn't been pressed):
	{}
	motor[motorA] = 0;
	if(valeurCapteurLumiere >= 170 && valeurCapteurLumiere <= 380)
	{
		return 1; //noir
	}
	else if(valeurCapteurLumiere > 380 && valeurCapteurLumiere <= 430)
	{
		return 2; //bleu
	}
	else if(valeurCapteurLumiere > 430 && valeurCapteurLumiere <= 480)
	{
		return 3; //vert
	}
	else if(valeurCapteurLumiere > 480 && valeurCapteurLumiere <= 530)
	{
		return 4; //jaune
	}
	else if(valeurCapteurLumiere > 530 && valeurCapteurLumiere <= 580)
	{
		return 5; //jaune
	}
}

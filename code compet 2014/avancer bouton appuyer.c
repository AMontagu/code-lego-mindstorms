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
int avancerDroite(int nombreTour);
int avancerGauche(int nombreTour);
void reculerGauche(int nombreTour);
void reculerDroite(int nombreTour);
void reculer(int nombreTour);
int avancer(int nombreTour);

task main()
{
	while(true)
	{
		avancerObstacle(30);
	}
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
		if(speed > 80)
		{
			speed = 80;
		}
		motor[motorA] = speed;
		sonarValue = SensorValue(sonarSensor);
		valeurBtnGauche = SensorValue(capteurTouchGauche);
		valeurBtnDroite = SensorValue(capteurTouchDroite);
		//nxtDisplayCenteredTextLine(5,"droite %d", valeurBtnDroite);
		//nxtDisplayCenteredTextLine(7,"gauche %d", valeurBtnGauche);
	}
	motor[motorA] = 0;
	if(valeurBtnGauche < 1000)
	{
		reculerDroite(200);
		wait1Msec(200);
		avancerDroite(400);
	}
	else if(valeurBtnDroite < 1000)
	{
		reculerGauche(200);
		wait1Msec(200);
		avancerGauche(400);
	}
}

int avancer(int nombreTour)
{
	nSyncedMotors = synchAB;
  nSyncedTurnRatio = 100;
  nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = nombreTour;
	motor[motorA] = 60;
	while(nMotorRunState[motorA] != runStateIdle)
	{}
	motor[motorA] = 0;
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

int avancerDroite(int nombreTour)
{
	nxtDisplayCenteredTextLine(3,"rentreD");
	int sonarValue = 0;
	nSyncedMotors = synchAB;
	nSyncedTurnRatio = 50;
	nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = nombreTour;
	motor[motorA] = 60;
	sonarValue = SensorValue(sonarSensor);
	while(sonarValue > 15 && nMotorRunState[motorA] != runStateIdle)
	{
		sonarValue = SensorValue(sonarSensor);
	}
	motor[motorA] = 0;
	return 1;
}

int avancerGauche(int nombreTour)
{
	nxtDisplayCenteredTextLine(1,"rentre");
	int sonarValue = 0;
	nSyncedMotors = synchBA;
	nSyncedTurnRatio = 50;
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = nombreTour;
	motor[motorB] = 60;
	sonarValue = SensorValue(sonarSensor);
	while(sonarValue > 15 && nMotorRunState[motorB] != runStateIdle)
  {
  	sonarValue = SensorValue(sonarSensor);
  }
  motor[motorB] = 0;
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

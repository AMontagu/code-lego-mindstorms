#pragma config(Sensor, S2,     capteurTouchGauche,         sensorTouch)
#pragma config(Sensor, S3,     capteurTouchDroite,         sensorTouch)

task main()
{
	int valeurCapteurDroit; // 1023 bouton relacher 183 bouton appuyer
	int valeurCapteurGauche;
	while(1)
	{
		valeurCapteurDroit = SensorValue(capteurTouchDroite);
	  valeurCapteurGauche = SensorValue(capteurTouchGauche);
		nxtDisplayTextLine(2, "%d", valeurCapteurDroit);
		nxtDisplayTextLine(4, "%d", valeurCapteurGauche);
	}
}

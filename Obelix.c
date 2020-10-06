#pragma config(Motor,  motorA,          motorRight,    tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          motorLeft,     tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define sensorFront S4

#include "config.c"
#include "position.c"
#include "movement.c"
#include "sonar.c"

task emergencyStop() {
	//while (SensorValue[redButton] == 0) { wait1Msec(20); }
	stopAllTasks();
}

task displayPos() {
	struct PosData pos;
	while (true) {
		wait1Msec(200);
		getRawPosition(&pos);
		displayBigTextLine(1, "X %5.1f", pos.x);
		displayBigTextLine(3, "Y %5.1f", pos.y);
		displayBigTextLine(5, "O %5.1f", pos.orientation);
	}
}


task main()
{
  initConfig(OBELIX);

  bool blueSide = true;
  // Yellow : � droite si on a les manches � air devant

  initPosition(blueSide);

  //startTask(avoidObstacles);


  const int nbPoints = 10;


	int points[2*nbPoints] = {
		460, 1100,
		380, 1650,
		540, 1740,
		1090, 1650,
		1110, 1200,
		1500, 700,
		1880, 700,
		1880, 350,
		1880, 800,
		900, 350
	};

	// On change la liste si c'est le cote jaune
	if(!blueSide){
	  for(int i = 0; i < nbPoints*2; i+=2){
			points[i] = 3000-points[i];
		}
	}

	bool isForward[nbPoints] = {true, true, true
		, true, true, true, true, true, false, true};

  for(int i = 0; i < nbPoints*2; i+=2){
  	char str[10];
  	sprintf(str, "i : %i", i);
    displayBigTextLine(1, str);

    if(isForward[i/2]){
  		moveTo_forward(points[i], points[i+1]);
  	}
  	else{
  		moveTo_backward(points[i], points[i+1]);
  	}

	}

	wait1Msec(20000);

  while (getMovementState() != NOMVT) {wait1Msec(20);}
}

/*
POSITIONS DES CUPS

d�part ~
30, 900 facing est

cup rouge
300, 400

cup verte
450, 510

cup rouge
670, 100

cup verte
950, 400

cup rouge
1100, 800

cup verte
1270, 1200


cup verte : passer 10cm � droite de facing
cup rouge : passer 10cm � gauche de facing

*/

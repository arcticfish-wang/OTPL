/**
create on:2018-01-05
author:LiBing
*/
#include"mp_elliptic.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<engine.h>
#include<MatlabEnginePlot.h>

int main()
{
	double n = 2;
	double t0 = 0;
	double t1 = 8;
	double q0 = 0;
	double q1 = 10;
	double dT = 1.0E-1;
	double *data[6] = { NULL };
	int dataNum = 0;
	int ret = 0;

	//call harmonic trajectory planning function
	if ((ret = mp_elliptic_traj(n,t0, t1, q0, q1, dT, data, &dataNum)) != 0)
		printf("call <mp_elliptic_traj> error: %d\n", ret);
	printf("call <mp_elliptic_traj> succeed!\n");
	for (int i = 0; i < dataNum; i++)
		printf("%f,%f,%f,%f\n", data[0][i], data[1][i], data[2][i], data[3][i]);

	//µ÷ÓÃmatlabÒýÇæ»æÍ¼
	Engine* eg = NULL;
	mat_engOpen(&eg);
	mat_clc(eg);
	mat_clear(eg);
	mat_subplot(eg, 3, 1, 1);
	mat_plot(eg, data[0], data[1], dataNum, "-r", 1, 5);
	mat_ylabel(eg, "position");
	mat_gridon(eg);
	mat_subplot(eg, 3, 1, 2);
	mat_plot(eg, data[0], data[2], dataNum, "-b", 1, 5);
	mat_ylabel(eg, "velocity");
	mat_gridon(eg);
	mat_subplot(eg, 3, 1, 3);
	mat_plot(eg, data[0], data[3], dataNum, "-k", 1, 5);
	mat_ylabel(eg, "acceleration");
	mat_gridon(eg);
	//mat_subplot(eg, 4, 1, 4);
	//mat_plot(eg, data[0], data[4], dataNum, "-g", 1, 5);
	//mat_ylabel(eg, "jerk");
	//mat_gridon(eg);
	mat_setgcf(eg, "color", "w");

	//

	for (int i = 0; i < 6; i++)
	{
		free(data[i]);
	}
	getchar();
	mat_engClose(&eg);
	return 0;
}
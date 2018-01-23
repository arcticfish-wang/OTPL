/**
create on:2018-01-05
author:LiBing
*/
#include"mp_harmonic.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<engine.h>
#include<MatlabEnginePlot.h>

int main()
{
	double t0 = 0;
	double t1 = 8;
	double q0 = 0;
	double q1 = 10;
	double dT = 1.0E-1;
	double *data[5] = { NULL };
	int dataNum = 0;
	int ret = 0;
	
	Engine* eg = NULL;
	mat_engOpen(&eg);
	//call harmonic trajectory planning function
	if ((ret = mp_harmonic_traj(t0, t1, q0, q1, dT, data,&dataNum)) != 0)
		printf("call 'mp_harmonic_traj' error: %d\n", ret);
	printf("call <mp_harmonic_traj> succeed!\n");
	for (int i = 0; i < dataNum; i++)
		printf("%f,%f,%f,%f,%f\n", data[0][i], data[1][i], data[2][i], data[3][i], data[4][i]);

	mat_subplot(eg, 4, 1, 1);
	mat_plot(eg, data[0],data[1], dataNum, "-k", 1, 5);
	mat_ylabel(eg,"position");
	mat_subplot(eg, 4, 1, 2);
	mat_plot(eg, data[0], data[2], dataNum, "-k", 1, 5);
	mat_ylabel(eg, "velocity");
	mat_subplot(eg, 4, 1, 3);
	mat_plot(eg, data[0], data[3], dataNum, "-k", 1, 5);
	mat_ylabel(eg, "acceleration");
	mat_subplot(eg, 4, 1, 4);
	mat_plot(eg, data[0], data[4], dataNum, "-k", 1, 5);
	mat_ylabel(eg, "jerk");
	mat_gridon(eg);
	for (int i = 0; i < 5; i++)
	{
		free(data[i]);
	}
	getchar();
	mat_engClose(eg);
	return 0;
}
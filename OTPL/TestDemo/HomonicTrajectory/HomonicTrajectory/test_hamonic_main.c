/**
create on:2018-01-05
author:LiBing
*/
#include"mp_harmonic.h"
#include<stdio.h>
int main()
{
	double t0 = 0;
	double t1 = 1;
	double q0 = 0;
	double q1 = 1;
	double dT = 1.0E-3;
	mp_para mpst;
	int ret = 0;
	if ((ret = mp_harmonic_traj(&t0, &t1, &q0, &q1, &dT, &mpst)) != 0)
		printf("call 'mp_harmonic_traj' error: %d\n", ret);

	return 0;
}
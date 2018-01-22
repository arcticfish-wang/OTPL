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
	//double t0 = 0;
	//double t1 = 8;
	//double q0 = 0;
	//double q1 = 10;
	//double dT = 1.0E-1;
	//double *data[5] = { NULL };
	//int dataNum = 0;
	//int ret = 0;
	//
	//if ((ret = mp_harmonic_traj(t0, t1, q0, q1, dT, data,&dataNum)) != 0)
	//	printf("call 'mp_harmonic_traj' error: %d\n", ret);
	//printf("call <mp_harmonic_traj> succeed!\n");
	//for (int i = 0; i < dataNum; i++)
	//	printf("%f,%f,%f,%f,%f\n", data[0][i], data[1][i], data[2][i], data[3][i], data[4][i]);
	

	
	//for (int i = 0; i < dataNum; i++)
	//{
	//	xtemp[i] = data[0][i];
	//	ytemp[i] = data[1][i];
	//}

	//mat_plot(eg, xtemp, ytemp, dataNum, "-r", 1, 5);
	//for (int i = 0; i < 5; i++)
	//{
	//	free(data[i]);
	//}
	#define dataNum 100
	int ret = 0;
	Engine* eg = NULL;
	if (!(eg = engOpen(NULL)))
	{
		printf("Open matlab enging fail!");
		return 1;
	}
	double xtemp[dataNum] = { 0 };
	double ytemp[dataNum] = { 0 };
	for (int i = 0; i < dataNum; i++)
	{
		xtemp[i] = i * 2.0 * 3.1415926 / 100.0;
		ytemp[i] = sin(xtemp[i]);

	}
	mxArray *X = mxCreateDoubleMatrix(1, dataNum, mxREAL);//创建matlab存储数据的指针
	mxArray *Y = mxCreateDoubleMatrix(1, dataNum, mxREAL);
	
	memcpy(mxGetPr(X), xtemp, dataNum * sizeof(double)); //数据复制
	memcpy(mxGetPr(Y), ytemp, dataNum * sizeof(double));

	if ((ret = engPutVariable(eg, "X", X)) != 0)   //把数据传递到matlab工作空间
		printf("engPutVariable error：%d\n", ret);
	if ((ret = engPutVariable(eg, "Y", Y)) != 0)
		printf("engPutVariable error：%d\n", ret);
	getchar();
	if(eg)
		engClose(eg);
	return 0;
}
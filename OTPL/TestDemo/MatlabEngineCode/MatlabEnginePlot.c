/**
@file MatlabEnginePlot.c
@brief plot using matlab engine
*/
#include<stdio.h>
#include<string.h>
#include "MatlabEnginePlot.h"
int mat_engOpen(Engine **eg)
{
	if (!(*eg = engOpen(NULL)))
	{
		printf("open matlab engine failed!\n");
		return 1;
	}
	printf("open matlab engine succeed!\n");
	return 0;
}

int mat_plot(Engine *eg, double *x, double *y, int N, char *LineStyle, double LineWidth, double MarkerSize)
{
	int ret = 0;
	mxArray *X = mxCreateDoubleMatrix(1, N, mxREAL);
	mxArray *Y = mxCreateDoubleMatrix(1, N, mxREAL);
	mxArray *MS = mxCreateDoubleScalar(MarkerSize);
	memcpy(mxGetPr(X), x, N * sizeof(double));
	memcpy(mxGetPr(Y), y, N * sizeof(double));

	if ((ret = engPutVariable(eg, "X", X)) != 0)
		printf("engPutVariable error£º%d\n", ret);
	if ((ret = engPutVariable(eg, "Y", Y)) != 0)
		printf("engPutVariable error£º%d\n", ret);

	//gennerate the plot command
	char plotCommand[256] = "fig=plot(X,Y,'";
	//set line style and marker
	if (strlen(LineStyle) > 0)
		strncat(plotCommand, LineStyle, strlen(LineStyle));
	else
	{
		strncat(plotCommand, "-", strlen("-"));
	}
	strncat(plotCommand, "',", strlen(LineStyle));

	char temp[20] = "";
	//set line width
	if (LineWidth < 1.0)
		LineWidth = 1.0;
	strncat(plotCommand, "'LineWidth',", strlen("'LineWidth',"));
	memset(temp, 0, sizeof(temp));
	sprintf(temp, "%f,", LineWidth);
	strncat(plotCommand, temp, strlen(temp));

	//set marker size
	strncat(plotCommand, "'MarkerSize',", strlen("'MarkerSize',"));
	sprintf(temp, "%f", MarkerSize);
	strncat(plotCommand, temp, strlen(temp));
	strncat(plotCommand, ");", strlen(temp));

	//plot
	if ((ret = engEvalString(eg, plotCommand)) != 0)
	{
		printf("\nplot Command error£º%s\n", plotCommand);
		return ret;
	}
	engEvalString(eg, "set(gcf,'color','w');");
	printf("plot Command ok£º%s\n", plotCommand);
	//destroy mxArray,but they are still in matlab workspace
	mxDestroyArray(X);
	mxDestroyArray(Y);
	return 0;
}
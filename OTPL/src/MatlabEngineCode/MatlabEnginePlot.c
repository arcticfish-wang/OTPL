/**
@file MatlabEnginePlot.c
@brief plot using matlab engine
*/
#include<stdio.h>
#include<string.h>
#include "MatlabEnginePlot.h"

#define CMMDTEMP 64  ///<临时命令长度（字符个数）
#define CMMDLEN 256  ///<命令最大长度（字符个数）
int mat_engOpen(Engine **eg)
{
	if (!(*eg=(engOpen(NULL))))
	{
		printf("open matlab engine failed!\n");
		return ENGOPEN_ERR;
	}
	printf("open matlab engine succeed!\n");
	return CMMD_OK;
}

int mat_engClose(Engine **eg)
{
	if (!(engClose(*eg)))
	{
		printf("close matlab engine failed!\n");
		return ENGCLOSE_ERR;
	}
	return CMMD_OK;
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
		printf("engPutVariable error：%d\n", ret);
	if ((ret = engPutVariable(eg, "Y", Y)) != 0)
		printf("engPutVariable error：%d\n", ret);

	//gennerate the plot command
	char plotCommand[CMMDLEN] = "fig=plot(X,Y,'";
	//set line style and marker
	if (strlen(LineStyle) > 0)
		strncat(plotCommand, LineStyle, strlen(LineStyle));
	else
	{
		strncat(plotCommand, "-", strlen("-"));
	}
	strncat(plotCommand, "',", strlen(LineStyle));

	char temp[CMMDTEMP] = "";
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
		printf("\nMatlab Command error：%s\n", plotCommand);
		return ret;
	}
	
	printf("\nMatlab Command ok：%s\n", plotCommand);
	//destroy mxArray,but they are still in matlab workspace
	mxDestroyArray(X);
	mxDestroyArray(Y);
	return CMMD_OK;
}


int mat_plot3(Engine *eg, double *x, double *y, double *z, int N, char *LineStyle, double LineWidth, double MarkerSize)
{
	int ret = 0;
	mxArray *X = mxCreateDoubleMatrix(1, N, mxREAL);
	mxArray *Y = mxCreateDoubleMatrix(1, N, mxREAL);
	mxArray *Z = mxCreateDoubleMatrix(1, N, mxREAL);
	mxArray *MS = mxCreateDoubleScalar(MarkerSize);
	memcpy(mxGetPr(X), x, N * sizeof(double));
	memcpy(mxGetPr(Y), y, N * sizeof(double));
	memcpy(mxGetPr(Z), z, N * sizeof(double));

	if ((ret = engPutVariable(eg, "X", X)) != 0)
		printf("engPutVariable error：%d\n", ret);
	if ((ret = engPutVariable(eg, "Y", Y)) != 0)
		printf("engPutVariable error：%d\n", ret);
	if ((ret = engPutVariable(eg, "Z", Z)) != 0)
		printf("engPutVariable error：%d\n", ret);

	//gennerate the plot command
	char plotCommand[CMMDLEN] = "fig=plot3(X,Y,Z,'";
	//set line style and marker
	if (strlen(LineStyle) > 0)
		strncat(plotCommand, LineStyle, strlen(LineStyle));
	else
	{
		strncat(plotCommand, "-", strlen("-"));
	}
	strncat(plotCommand, "',", strlen(LineStyle));

	char temp[CMMDTEMP] = "";
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
	if ((ret = engEvalString(eg, plotCommand)) != CMMD_OK)
	{
		printf("\nMatlab Command error：%s\n", plotCommand);
		return ret;
	}
	printf("\nMatlab Command ok：%s\n", plotCommand);
	//destroy mxArray,but they are still in matlab workspace
	mxDestroyArray(X);
	mxDestroyArray(Y);
	mxDestroyArray(Z);
	return CMMD_OK;
}

int mat_gridon(Engine *eg)
{
	int ret = 0;
	char command[CMMDLEN] = "grid on;";
	if ((ret = engEvalString(eg, command)) != CMMD_OK)
	{
		printf("\nMatlab Command error：%s\n", command);
		return ret;
	}
	return CMMD_OK;

}

int mat_holdon(Engine *eg)
{
	int ret = 0;
	char command[CMMDLEN] = "hold on;";
	if ((ret = engEvalString(eg, command)) != CMMD_OK)
	{
		printf("\nMatlab Command error：%s\n", command);
		return ret;
	}
	return CMMD_OK;
}

int mat_subplot(Engine *eg,int row,int col,int n)
{
	int ret;
	char temp[CMMDTEMP] = "";
	char command[CMMDLEN] = "subplot(";
	sprintf(temp, "%d,%d,%d);", row, col, n);
	strncat(command, temp, strlen(temp));
	if ((ret = engEvalString(eg, command)) != CMMD_OK)
	{
		printf("\nMatlab Command error：%s\n", command);
		return ret;
	}
	//printf("\nMatlab Command ok：%s\n", command);
	return CMMD_OK;
}

int mat_xlabel(Engine *eg, char *xlabel)
{
	int ret;
	char temp[CMMDTEMP] = "";
	char command[CMMDLEN] = "xlabel(";
	sprintf(temp, "'%s');", xlabel);
	strncat(command, temp, strlen(temp));
	if ((ret = engEvalString(eg, command)) != CMMD_OK)
	{
		printf("\nMatlab Command error：%s\n", command);
		return ret;
	}
	return CMMD_OK;
}

int mat_ylabel(Engine *eg, char *ylabel)
{
	int ret;
	char temp[CMMDTEMP] = "";
	char command[CMMDLEN] = "ylabel(";
	sprintf(temp, "'%s');", ylabel);
	strncat(command, temp, strlen(temp));
	if ((ret = engEvalString(eg, command)) != CMMD_OK)
	{
		printf("\nMatlab Command error：%s\n", command);
		return ret;
	}
	return CMMD_OK;
}

int mat_clc(Engine *eg)
{
	int ret;
	char temp[CMMDTEMP] = "";
	char command[CMMDLEN] = "clc;";
	if ((ret = engEvalString(eg, command)) != CMMD_OK)
	{
		printf("\nMatlab Command error：%s\n", command);
		return ret;
	}
	return CMMD_OK;
}

int mat_clear(Engine *eg)
{
	int ret;
	char temp[CMMDTEMP] = "";
	char command[CMMDLEN] = "clear;";
	if ((ret = engEvalString(eg, command)) != CMMD_OK)
	{
		printf("\nMatlab Command error：%s\n", command);
		return ret;
	}
	return CMMD_OK;
}

int mat_setgcf(Engine *eg,char *object,char *property)
{
	int ret;
	char temp[CMMDTEMP] = "";
	char command[CMMDLEN] = "set(gcf,";
	sprintf(temp, "'%s',", property);
	strncat(command, temp, strlen(temp));
	sprintf(temp, "'%s');", property);
	strncat(command, temp, strlen(temp));
	if ((ret = engEvalString(eg, command)) != CMMD_OK)
	{
		printf("\nMatlab Command error：%s\n", command);
		return ret;
	}
	return CMMD_OK;
}
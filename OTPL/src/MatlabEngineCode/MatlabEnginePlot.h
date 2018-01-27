#ifndef USEMATLABENGE_H_
#define USEMATLABENGE_H_
#include <engine.h>


#define CMMD_OK      0	  /**<command ok*/
#define CMMD_ERR     1	  /**<command ERROR*/
#define ENGOPEN_ERR  2   /**<open matlab engine error*/
#define ENGCLOSE_ERR 3   /**<close matlab engine error*/

#ifdef __cplusplus
extern "C" {
#endif // __cpluscplus

	int mat_engOpen(Engine **eg);
	int mat_engClose(Engine **eg);
	int mat_plot(Engine *eg, double *x, double *y, int N, char *LineStyle, double LineWidth, double MarkerSize);
	int mat_plot3(Engine *eg, double *x, double *y, double *z, int N, char *LineStyle, double LineWidth, double MarkerSize);
	int mat_gridon(Engine *eg);
	int mat_subplot(Engine *eg, int row, int col, int n);
	int mat_holdon(Engine *eg);
	int mat_xlabel(Engine *eg, char *xlabel);
	int mat_ylabel(Engine *eg, char *ylable);
	int mat_clc(Engine *eg);
	int mat_clear(Engine *eg);
	int mat_setgcf(Engine *eg, char *object, char *property);
#ifdef __cpluscplus
}
#endif
#endif
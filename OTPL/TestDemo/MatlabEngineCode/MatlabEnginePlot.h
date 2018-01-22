#ifndef USEMATLABENGE_H_
#define USEMATLABENGE_H_
#include <engine.h>

#ifdef __cplusplus
extern "C" {
#endif // __cpluscplus

	int mat_plot(Engine *eg, double *x, double *y, int N, char *LineStyle, double LineWidth, double MarkerSize);
	int mat_engOpen(Engine **eg);

#ifdef __cpluscplus
}
#endif
#endif
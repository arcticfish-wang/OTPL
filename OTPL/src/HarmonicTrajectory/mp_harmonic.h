/*harmonic_rajectory*/
#ifndef MP_HAMONIC_H_
#define MP_HAMONIC_H_

#ifdef __cplusplus  
extern "C" {
#endif // 



	int mp_harmonic_traj(double t0, double t1, double q0, double q1, double dT, double *data[5], int *dataNum);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
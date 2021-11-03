

/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif

/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>

#define PI 3.14159

#define unitNo 80
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 3
#define y_width 1
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
void windForceTower_Outputs_wrapper(const real_T *dxcm,
			const real_T *theta,
			const real_T *omega,
			const real_T *windSpeed,
			real_T *y0,
			const real_T *xD,
			const real_T  *towerR, const int_T  p_width0,
			const real_T  *towerL, const int_T  p_width1,
			const real_T  *windAlpha, const int_T  p_width2,
			const real_T  *rho, const int_T  p_width3,
			const real_T  *Cd, const int_T  p_width4,
			const real_T  *CoA, const int_T  p_width5)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* This sample sets the output equal to the input
      y0[0] = u0[0]; 
 For complex signals use: y0[0].re = u0[0].re; 
      y0[0].im = u0[0].im;
      y1[0].re = u1[0].re;
      y1[0].im = u1[0].im;
*/

y0[0] = xD[0];  // force[0]
y0[1] = xD[1];  // force[1]
y0[2] = xD[2];  // force[2]
y0[3] = xD[3];  // torque[0]
y0[4] = xD[4];  // torque[1]
y0[5] = xD[5];  // torque[2]
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
  * Updates function
  *
  */
void windForceTower_Update_wrapper(const real_T *dxcm,
			const real_T *theta,
			const real_T *omega,
			const real_T *windSpeed,
			const real_T *y0,
			real_T *xD,
			const real_T  *towerR,  const int_T  p_width0,
			const real_T  *towerL,  const int_T  p_width1,
			const real_T  *windAlpha,  const int_T  p_width2,
			const real_T  *rho,  const int_T  p_width3,
			const real_T  *Cd,  const int_T  p_width4,
			const real_T  *CoA,  const int_T  p_width5)
{
  /* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
double unitLen = towerL[0] / unitNo;
double unitPos = 0.0;
int i,j,k;
double Rotx[3] = { 0.0 };
double Roty[3] = { 0.0 };
double Rotz[3] = { 0.0 };

double unitVel[3] = { 0.0 }; // velocity with respect to world frame
double unitVelF[3] = { 0.0 };// velocity with respect to local frame
double fluidVel[3] = { 0.0 };
double fluidVelF[3] = { 0.0 };

double ForceF[2] = { 0.0 };
double TorqueF[2] = { 0.0 };
double unitForce[2] = { 0.0 };
double Force[3] = { 0.0 };
double Torque[3] = { 0.0 };

double z;  // position 

// unit vector of x-direction
Rotx[0] = cos(theta[1]) * cos(theta[2]);
Rotx[1] = cos(theta[1]) * sin(theta[2]);
Rotx[2] = -sin(theta[1]);

// unit vector of y-direction
Roty[0] = -cos(theta[0]) * sin(theta[2]) + sin(theta[0]) * 
        sin(theta[1]) * cos(theta[2]);
Roty[1] = cos(theta[0]) * cos(theta[2]) + sin(theta[0]) * 
        sin(theta[1]) * sin(theta[2]);
Roty[2] = sin(theta[0]) * cos(theta[1]);

// unit vector of z-direction
Rotz[0] = sin(theta[0]) * sin(theta[2]) + cos(theta[0]) *
        sin(theta[1]) * cos(theta[2]);
Rotz[1] = -sin(theta[0]) * cos(theta[2]) + cos(theta[0]) *
        sin(theta[1]) * sin(theta[2]);
Rotz[2] = cos(theta[0]) * cos(theta[1]);

for(i = 0; i < unitNo; i++) {
    z = i * unitLen;  
    unitPos = z - CoA[0];
    fluidVel[0] = windSpeed[0] * pow( z / towerL[0], windAlpha[0]);
    fluidVel[1] = windSpeed[1] * pow(z / towerL[0], windAlpha[0]);
    fluidVel[2] = 0.0;
  
    unitVel[0] = dxcm[0] + (omega[1] * Rotz[2] - omega[2] * Rotz[1]) * unitPos;
    unitVel[1] = dxcm[1] - (omega[0] * Rotz[2] - omega[2] * Rotz[0]) * unitPos;
    unitVel[2] = dxcm[2] + (omega[0] * Rotz[1] - omega[1] * Rotz[0]) * unitPos;
    
    // transform to local frame   
    unitVelF[0] = Rotx[0] * unitVel[0] + Rotx[1] * unitVel[1] + Rotx[2] * unitVel[2];
    unitVelF[1] = Roty[0] * unitVel[0] + Roty[1] * unitVel[1] + Roty[2] * unitVel[2];
    unitVelF[2] = Rotz[0] * unitVel[0] + Rotz[1] * unitVel[1] + Rotz[2] * unitVel[2];

    fluidVelF[0] = Rotx[0] * fluidVel[0] + Rotx[1] * fluidVel[1] + Rotx[2] * fluidVel[2];
    fluidVelF[1] = Roty[0] * fluidVel[0] + Roty[1] * fluidVel[1] + Roty[2] * fluidVel[2];
    fluidVelF[2] = Rotz[0] * fluidVel[0] + Rotz[1] * fluidVel[1] + Rotz[2] * fluidVel[2];
    
    unitForce[0] = 0.5 * rho[0] * 2.0 * towerR[0] * Cd[0] * (fluidVelF[0] - unitVelF[0]) * fabs(fluidVelF[0] - unitVelF[0]);
    unitForce[1] = 0.5 * rho[0] * 2.0 * towerR[0] * Cd[0] * (fluidVelF[1] - unitVelF[1]) * fabs(fluidVelF[1] - unitVelF[1]);
    
    ForceF[0] += unitForce[0] * unitLen;
    ForceF[1] += unitForce[1] * unitLen;
    
    TorqueF[0] += - unitForce[1] * unitLen * unitPos;
    TorqueF[1] += unitForce[0] * unitLen * unitPos;
}


Force[0] = Rotx[0] * ForceF[0] + Roty[0] * ForceF[1] + 0.0;
Force[1] = Rotx[1] * ForceF[0] + Roty[1] * ForceF[1] + 0.0;
Force[2] = Rotx[2] * ForceF[0] + Roty[2] * ForceF[1] + 0.0;

Torque[0] = Rotx[0] * TorqueF[0] + Roty[0] * TorqueF[1] + 0.0;
Torque[1] = Rotx[1] * TorqueF[0] + Roty[1] * TorqueF[1] + 0.0;
Torque[2] = Rotx[2] * TorqueF[0] + Roty[2] * TorqueF[1] + 0.0;


xD[0] = Force[0];
xD[1] = Force[1];
xD[2] = Force[2];
xD[3] = Torque[0];
xD[4] = Torque[1];
xD[5] = Torque[2];
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}

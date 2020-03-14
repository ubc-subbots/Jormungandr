//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: xscal_myTCeGM2.cpp
//
// Code generated for Simulink model 'thrust_allocation'.
//
// Model version                  : 1.76
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Fri Mar 13 18:47:00 2020
//
#include "rtwtypes.h"
#include "xscal_myTCeGM2.h"

// Function for MATLAB Function: '<Root>/thrust_allocator'
void xscal_myTCeGM2(real_T a, real_T x[100], int32_T ix0)
{
  int32_T k;
  for (k = ix0; k <= ix0 + 9; k++) {
    x[k - 1] *= a;
  }
}

//
// File trailer for generated code.
//
// [EOF]
//

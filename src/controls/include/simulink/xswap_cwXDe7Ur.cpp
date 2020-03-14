//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: xswap_cwXDe7Ur.cpp
//
// Code generated for Simulink model 'thrust_allocation'.
//
// Model version                  : 1.76
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Fri Mar 13 18:47:00 2020
//
#include "rtwtypes.h"
#include "xswap_cwXDe7Ur.h"

// Function for MATLAB Function: '<Root>/thrust_allocator'
void xswap_cwXDe7Ur(real_T x[100], int32_T ix0, int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  real_T temp;
  int32_T k;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 10; k++) {
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix++;
    iy++;
  }
}

//
// File trailer for generated code.
//
// [EOF]
//

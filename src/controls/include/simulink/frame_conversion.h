//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: frame_conversion.h
//
// Code generated for Simulink model 'frame_conversion'.
//
// Model version                  : 1.30
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Fri Mar 13 18:45:48 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#ifndef RTW_HEADER_frame_conversion_h_
#define RTW_HEADER_frame_conversion_h_
#include <cmath>
#include <cstring>
#include <stddef.h>
#ifndef frame_conversion_COMMON_INCLUDES_
# define frame_conversion_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 // frame_conversion_COMMON_INCLUDES_

#include <stddef.h>

// Forward declaration for rtModel
typedef struct tag_RTM_frame_conversion_T RT_MODEL_frame_conversion_T;

// Real-time Model Data Structure
struct tag_RTM_frame_conversion_T {
  const char_T **errorStatus;
};

// Class declaration for model frame_conversion
class frame_conversionModelClass {
  // public data and function members
 public:
  // model step function
  void step(const real_T arg_nu[6], const real_T arg_eta[6], real_T arg_eta_dot
            [6]);

  // Constructor
  frame_conversionModelClass();

  // Destructor
  ~frame_conversionModelClass();

  // Real-Time Model get method
  RT_MODEL_frame_conversion_T * getRTM();

  //member function to setup error status pointer
  void setErrorStatusPointer(const char_T **rt_errorStatus);

  // private data and function members
 private:
  // Real-Time Model
  RT_MODEL_frame_conversion_T frame_conversion_M;
};

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'frame_conversion'
//  '<S1>'   : 'frame_conversion/MATLAB Function'

#endif                                 // RTW_HEADER_frame_conversion_h_

//
// File trailer for generated code.
//
// [EOF]
//

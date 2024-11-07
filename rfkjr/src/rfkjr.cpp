/*
 * rfkjr.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "rfkjr".
 *
 * Model version              : 1.4
 * Simulink Coder version : 24.1 (R2024a) 19-Nov-2023
 * C++ source code generated on : Thu Nov  7 10:33:26 2024
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "rfkjr.h"
#include "rtwtypes.h"
#include "rfkjr_types.h"
#include "rfkjr_private.h"
#include <string.h>

/* Block signals (default storage) */
B_rfkjr_T rfkjr_B;

/* Continuous states */
X_rfkjr_T rfkjr_X;

/* Disabled State Vector */
XDis_rfkjr_T rfkjr_XDis;

/* Block states (default storage) */
DW_rfkjr_T rfkjr_DW;

/* Real-time model */
RT_MODEL_rfkjr_T rfkjr_M_ = RT_MODEL_rfkjr_T();
RT_MODEL_rfkjr_T *const rfkjr_M = &rfkjr_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = static_cast<ODE3_IntgData *>(rtsiGetSolverData(si));
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  rfkjr_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  rfkjr_step();
  rfkjr_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  rfkjr_step();
  rfkjr_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void rfkjr_step(void)
{
  SL_Bus_rfkjr_std_msgs_Float64 rtb_BusAssignment;
  SL_Bus_rfkjr_std_msgs_Float64 rtb_SourceBlock_o2_0;
  boolean_T b_varargout_1;
  if (rtmIsMajorTimeStep(rfkjr_M)) {
    /* set solver stop time */
    if (!(rfkjr_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&rfkjr_M->solverInfo, ((rfkjr_M->Timing.clockTickH0
        + 1) * rfkjr_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&rfkjr_M->solverInfo, ((rfkjr_M->Timing.clockTick0 +
        1) * rfkjr_M->Timing.stepSize0 + rfkjr_M->Timing.clockTickH0 *
        rfkjr_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(rfkjr_M)) {
    rfkjr_M->Timing.t[0] = rtsiGetT(&rfkjr_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(rfkjr_M)) {
    /* Outputs for Atomic SubSystem: '<Root>/Subscribe' */
    /* MATLABSystem: '<S4>/SourceBlock' */
    b_varargout_1 = Sub_rfkjr_16.getLatestMessage(&rtb_SourceBlock_o2_0);

    /* Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
     *  EnablePort: '<S6>/Enable'
     */
    /* Start for MATLABSystem: '<S4>/SourceBlock' */
    if (b_varargout_1) {
      /* SignalConversion generated from: '<S6>/In1' */
      rfkjr_B.In1 = rtb_SourceBlock_o2_0;
    }

    /* End of Start for MATLABSystem: '<S4>/SourceBlock' */
    /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem' */
    /* End of Outputs for SubSystem: '<Root>/Subscribe' */
  }

  /* Integrator: '<S5>/Integrator' */
  if (rfkjr_DW.Integrator_IWORK != 0) {
    rfkjr_X.Integrator_CSTATE = rfkjr_B.In1.Data;
  }

  /* Saturate: '<S5>/Saturation' incorporates:
   *  Integrator: '<S5>/Integrator'
   */
  if (rfkjr_X.Integrator_CSTATE > rfkjr_P.Saturation_UpperSat) {
    /* BusAssignment: '<Root>/Bus Assignment' */
    rtb_BusAssignment.Data = rfkjr_P.Saturation_UpperSat;
  } else if (rfkjr_X.Integrator_CSTATE < rfkjr_P.Saturation_LowerSat) {
    /* BusAssignment: '<Root>/Bus Assignment' */
    rtb_BusAssignment.Data = rfkjr_P.Saturation_LowerSat;
  } else {
    /* BusAssignment: '<Root>/Bus Assignment' */
    rtb_BusAssignment.Data = rfkjr_X.Integrator_CSTATE;
  }

  /* End of Saturate: '<S5>/Saturation' */

  /* Outputs for Atomic SubSystem: '<Root>/Publish' */
  /* MATLABSystem: '<S3>/SinkBlock' */
  Pub_rfkjr_17.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish' */
  if (rtmIsMajorTimeStep(rfkjr_M)) {
    /* MATLAB Function: '<Root>/MATLAB Function1' */
    rfkjr_B.accel_desired = (50.0 - rfkjr_B.In1.Data) * 0.1;
  }

  /* TransferFcn: '<S5>/Transfer Fcn' */
  rfkjr_B.TransferFcn = rfkjr_P.TransferFcn_C * rfkjr_X.TransferFcn_CSTATE;
  if (rtmIsMajorTimeStep(rfkjr_M)) {
    /* Update for Integrator: '<S5>/Integrator' */
    rfkjr_DW.Integrator_IWORK = 0;
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(rfkjr_M)) {
    rt_ertODEUpdateContinuousStates(&rfkjr_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++rfkjr_M->Timing.clockTick0)) {
      ++rfkjr_M->Timing.clockTickH0;
    }

    rfkjr_M->Timing.t[0] = rtsiGetSolverStopTime(&rfkjr_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.1s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.1, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      rfkjr_M->Timing.clockTick1++;
      if (!rfkjr_M->Timing.clockTick1) {
        rfkjr_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void rfkjr_derivatives(void)
{
  XDot_rfkjr_T *_rtXdot;
  _rtXdot = ((XDot_rfkjr_T *) rfkjr_M->derivs);

  /* Derivatives for Integrator: '<S5>/Integrator' */
  _rtXdot->Integrator_CSTATE = rfkjr_B.TransferFcn;

  /* Derivatives for TransferFcn: '<S5>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = rfkjr_P.TransferFcn_A *
    rfkjr_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += rfkjr_B.accel_desired;
}

/* Model initialize function */
void rfkjr_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rfkjr_M->solverInfo, &rfkjr_M->Timing.simTimeStep);
    rtsiSetTPtr(&rfkjr_M->solverInfo, &rtmGetTPtr(rfkjr_M));
    rtsiSetStepSizePtr(&rfkjr_M->solverInfo, &rfkjr_M->Timing.stepSize0);
    rtsiSetdXPtr(&rfkjr_M->solverInfo, &rfkjr_M->derivs);
    rtsiSetContStatesPtr(&rfkjr_M->solverInfo, (real_T **) &rfkjr_M->contStates);
    rtsiSetNumContStatesPtr(&rfkjr_M->solverInfo, &rfkjr_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&rfkjr_M->solverInfo,
      &rfkjr_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&rfkjr_M->solverInfo,
      &rfkjr_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&rfkjr_M->solverInfo,
      &rfkjr_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&rfkjr_M->solverInfo, (boolean_T**)
      &rfkjr_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&rfkjr_M->solverInfo, (&rtmGetErrorStatus(rfkjr_M)));
    rtsiSetRTModelPtr(&rfkjr_M->solverInfo, rfkjr_M);
  }

  rtsiSetSimTimeStep(&rfkjr_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&rfkjr_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&rfkjr_M->solverInfo, false);
  rfkjr_M->intgData.y = rfkjr_M->odeY;
  rfkjr_M->intgData.f[0] = rfkjr_M->odeF[0];
  rfkjr_M->intgData.f[1] = rfkjr_M->odeF[1];
  rfkjr_M->intgData.f[2] = rfkjr_M->odeF[2];
  rfkjr_M->contStates = ((X_rfkjr_T *) &rfkjr_X);
  rfkjr_M->contStateDisabled = ((XDis_rfkjr_T *) &rfkjr_XDis);
  rfkjr_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&rfkjr_M->solverInfo, static_cast<void *>(&rfkjr_M->intgData));
  rtsiSetSolverName(&rfkjr_M->solverInfo,"ode3");
  rtmSetTPtr(rfkjr_M, &rfkjr_M->Timing.tArray[0]);
  rfkjr_M->Timing.stepSize0 = 0.1;
  rtmSetFirstInitCond(rfkjr_M, 1);

  /* block I/O */
  (void) memset((static_cast<void *>(&rfkjr_B)), 0,
                sizeof(B_rfkjr_T));

  /* states (continuous) */
  {
    (void) memset(static_cast<void *>(&rfkjr_X), 0,
                  sizeof(X_rfkjr_T));
  }

  /* disabled states */
  {
    (void) memset(static_cast<void *>(&rfkjr_XDis), 0,
                  sizeof(XDis_rfkjr_T));
  }

  /* states (dwork) */
  (void) memset(static_cast<void *>(&rfkjr_DW), 0,
                sizeof(DW_rfkjr_T));

  {
    char_T b_zeroDelimTopic_0[21];
    char_T b_zeroDelimTopic[17];
    static const char_T b_zeroDelimTopic_1[17] = "/car/state/vel_x";
    static const char_T b_zeroDelimTopic_2[21] = "/car/state/sim_vel_x";

    /* Start for Atomic SubSystem: '<Root>/Subscribe' */
    /* Start for MATLABSystem: '<S4>/SourceBlock' */
    rfkjr_DW.obj_p.matlabCodegenIsDeleted = false;
    rfkjr_DW.objisempty = true;
    rfkjr_DW.obj_p.isInitialized = 1;
    for (int32_T i = 0; i < 17; i++) {
      b_zeroDelimTopic[i] = b_zeroDelimTopic_1[i];
    }

    Sub_rfkjr_16.createSubscriber(&b_zeroDelimTopic[0], 1);
    rfkjr_DW.obj_p.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S4>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe' */

    /* Start for Atomic SubSystem: '<Root>/Publish' */
    /* Start for MATLABSystem: '<S3>/SinkBlock' */
    rfkjr_DW.obj.matlabCodegenIsDeleted = false;
    rfkjr_DW.objisempty_m = true;
    rfkjr_DW.obj.isInitialized = 1;
    for (int32_T i = 0; i < 21; i++) {
      b_zeroDelimTopic_0[i] = b_zeroDelimTopic_2[i];
    }

    Pub_rfkjr_17.createPublisher(&b_zeroDelimTopic_0[0], 1);
    rfkjr_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S3>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish' */
  }

  /* InitializeConditions for Integrator: '<S5>/Integrator' */
  if (rtmIsFirstInitCond(rfkjr_M)) {
    rfkjr_X.Integrator_CSTATE = 0.0;
  }

  rfkjr_DW.Integrator_IWORK = 1;

  /* End of InitializeConditions for Integrator: '<S5>/Integrator' */

  /* InitializeConditions for TransferFcn: '<S5>/Transfer Fcn' */
  rfkjr_X.TransferFcn_CSTATE = 0.0;

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe' */
  /* SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem' */
  /* SystemInitialize for SignalConversion generated from: '<S6>/In1' incorporates:
   *  Outport: '<S6>/Out1'
   */
  rfkjr_B.In1 = rfkjr_P.Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe' */

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(rfkjr_M)) {
    rtmSetFirstInitCond(rfkjr_M, 0);
  }
}

/* Model terminate function */
void rfkjr_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Subscribe' */
  /* Terminate for MATLABSystem: '<S4>/SourceBlock' */
  if (!rfkjr_DW.obj_p.matlabCodegenIsDeleted) {
    rfkjr_DW.obj_p.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S4>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Subscribe' */

  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S3>/SinkBlock' */
  if (!rfkjr_DW.obj.matlabCodegenIsDeleted) {
    rfkjr_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S3>/SinkBlock' */
  /* End of Terminate for SubSystem: '<Root>/Publish' */
}

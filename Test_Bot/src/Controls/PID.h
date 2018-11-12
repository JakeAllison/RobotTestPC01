#ifndef PID_h_
#define PID_h_

// Variables:
// kp - Proportional gain
// ki - Integral gain
// kd - Derivative gain
//
// p_max - The amount of error at which the proportional component is at its max output
// i_sum - Integral summation
// i_max - Maximum integral summation
// d_sum - Summation for fading-memory filter
// d_filter - Multiplier to use for fading memory filter
//
// max_output - Maximum output of the filter
// max_acceleration - Max acceleration per unit time
// epsilon - Tolerance for system settling
//
// previous_error - Error from previous calculation
// previous_output - Output from the previous processing cycle
// settling_time - Amount of time since the system was within settling tolerance

#include <Defines.h>

class PID_Calc
{
public:
    enum PID_Control_Mode {
        kPIDControlModeNoControl,
        kPIDControlModePositionControl,
        kPIDControlModeSpeedControl
    };

    PID_Calc();
    void Full_Reset();
    void Reset();

    void Set_Multipliers(double K_P, double K_I, double K_D);
    int Set_Parameters(double Epsilon, PID_Calc::PID_Control_Mode Control_Mode,
                       double Max_Output = 0, double Max_Acceleration = 0, double P_Max = 0, double I_Max = 0,
                       double D_Filter = 1, bool Is_Continuous = false, double Rotation_Min = 0.0,
                       double Rotation_Max = 0.0);

    double Calc_PID(double Point_Value, double Destination, double Time_Interval);
    bool Is_Done(double Settling_Time);

    int Get_Error()
    {
        return errorcode;
    };
    void Reset_Error()
    {
        errorcode = 0;
    };

private:
    double kp, ki, kd;

    double p_max;
    double i_sum, i_max;
    double d_sum, d_filter;

    double max_output;
    double max_acceleration;
    double epsilon;
    double rotmax;
    double rotmin;
    bool iscontinuous;

    double previous_error;
    double previous_output;
    double settling_time;

    unsigned int errorcode;

    PID_Control_Mode controlMode;
};

// Error codes:
// - 0x0001: P_Max out of range. (P_Max >= 0)
// - 0x0002: I_Max out of range. (I_Max >= 0)
// - 0x0004: D_Filter out of range. (0 < D_Filter <= 1)
// - 0x0008: Max_Output out of range. (Max_Output >= 0)
// - 0x0010: Max_Acceleration out of range. (Max_Acceleration >= 0)
// - 0x0020: Epsilon out of range. (Epsilon >= 0)
// - 0x0040: Bad time interval input. (time interval > 0)
// - 0x0080: Bad time_interval calculated. (time_interval > 0)
// - 0x0100: Bad control mode. (speed or position)
// - 0x0200: Bad rotation range when enabling continuous mode. (rotmax > rotmin)
#endif

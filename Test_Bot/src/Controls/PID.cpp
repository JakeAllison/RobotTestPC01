#include <Controls/PID.h>
#include <math.h>

// Initializes the PID program.
PID_Calc::PID_Calc()
{
    Reset();
}

// Sets all variables to zero and resets the PID program.
void PID_Calc::Full_Reset()
{
    // P, I, and D gain values
    kp = 0;
    ki = 0;
    kd = 0;

    // PID internal variables
    p_max = 0;
    i_sum = 0;
    i_max = 0;
    d_sum = 0;
    d_filter = 0;

    // General parameters
    max_output = 0;
    max_acceleration = 0;
    epsilon = 0;
    rotmin = 0;
    rotmax = 0;
    iscontinuous = false;

    // Data from previous processing cycles
    previous_error = 0;
    previous_output = 0;
    settling_time = 0;

    controlMode = PID_Calc::PID_Control_Mode::kPIDControlModeNoControl;

    errorcode = 0;
}

// Sets memory data to zero.
void PID_Calc::Reset()
{
    i_sum = 0;
    d_sum = 0;
    previous_error = 0;
    previous_output = 0;
    settling_time = 0;
}

// Sets P, I, and D multipliers.
void PID_Calc::Set_Multipliers(double K_P, double K_I, double K_D)
{
    kp = K_P;
    ki = K_I;
    kd = K_D;
}

// Sets PID all parameters.
int PID_Calc::Set_Parameters(double Epsilon, PID_Calc::PID_Control_Mode Control_Mode,
                             double Max_Output, double Max_Acceleration, double P_Max, double I_Max, double D_Filter,
                             bool Is_Continuous, double Rotation_Min, double Rotation_Max)
{

    errorcode = 0;

    if (P_Max >= 0)
    {
        p_max = P_Max;
    }
    else
    {
        p_max = 0;
        errorcode |= 0x0001;
    }

    if (I_Max >= 0)
    {
        i_max = I_Max;
    }
    else
    {
        i_max = 0;
        errorcode |= 0x0002;
    }

    if ((D_Filter >= 0) && (D_Filter <= 1))
    {
        d_filter = D_Filter;
    }
    else
    {
        d_filter = 0;
        errorcode |= 0x0004;
    }

    if (Max_Output >= 0)
    {
        max_output = Max_Output;
    }
    else
    {
        max_output = 0;
        errorcode |= 0x0008;
    }

    if (Max_Acceleration >= 0)
    {
        max_acceleration = Max_Acceleration;
    }
    else
    {
        max_acceleration = 0;
        errorcode |= 0x0010;
    }

    if (Epsilon >= 0)
    {
        epsilon = Epsilon;
    }
    else
    {
        epsilon = 0;
        errorcode |= 0x0020;
    }

    if (Control_Mode == PID_Calc::PID_Control_Mode::kPIDControlModePositionControl
            || Control_Mode == PID_Calc::PID_Control_Mode::kPIDControlModePositionControl)
    {
        controlMode = Control_Mode;
    }
    else
    {
        controlMode = PID_Calc::PID_Control_Mode::kPIDControlModeNoControl;
        errorcode |= 0x0040;
    }

    iscontinuous = Is_Continuous;

    if (iscontinuous)
    {
        if (rotmax > rotmin)
        {
            rotmin = Rotation_Min;
            rotmax = Rotation_Max;
        }
        else
        {
            iscontinuous = false;
            errorcode |= 0x0200;
        }
    }
    else
    {
        rotmin = 0;
        rotmax = 0;
    }

    return errorcode;
}

// Calculates the final output.
double PID_Calc::Calc_PID(double Point_Value, double Destination, double Time_Interval)
{
    double error;
    double p_value, i_value, d_value;
    double output;
    double accel_limit_high;
    double accel_limit_low;

    //------------------------------------------------------------------
    // Error calculation, time interval calculation, and
    // output limiting due to acceleration limits.
    //------------------------------------------------------------------

    error = Destination - Point_Value;
    error = ((error > epsilon) || (error < -epsilon)) ? error : 0;

    if (iscontinuous)
    {
        if (rotmax > rotmin)
        {

            // Wrap the error so that it's inside the acceptable range.
            // This will account for range errors for the destination too!

            while (error > rotmax)
            {
                error = error - (rotmax - rotmin);
            }

            while (error < rotmin)
            {
                error = error + (rotmax - rotmin);
            }

            if (error > (rotmax - rotmin) / 2)
            {
                error = error + (rotmax - rotmin);
            }
            else if (error < (rotmin - rotmax) / 2)
            {
                error = error + (rotmin - rotmax);
            }
        }
        else
        {
            errorcode |= 0x0200;
        }
    }

    if (Time_Interval < 0.0)
    {
        Time_Interval = 1.0;
        errorcode |= 0x0040;
    }
    else if (Time_Interval == 0.0)
    {
        Time_Interval = 1.0;
    }
    else
    {
        // Do nothing
    }

    if (Time_Interval <= 0)
    {
        accel_limit_high = 0;
        accel_limit_low = 0;
        errorcode |= 0x0080;
    }
    else if (max_acceleration != 0)
    {
        accel_limit_high = previous_output + max_acceleration * Time_Interval;
        accel_limit_low = previous_output - max_acceleration * Time_Interval;
    }
    else
    {
        accel_limit_high = 0;
        accel_limit_low = 0;
    }

    //------------------------------------------------------------------
    //              Calculate P, I, and D terms.
    //------------------------------------------------------------------

    // Calculate the P term.
    // This keeps the P value within it's defined limits.
    // P_Max = 0 means no limit or scaling.
    p_value = (error > p_max) ? p_max : ((error < -p_max) ? -p_max : error);

    if (p_max < 0)
    {
        p_value = 0;
        errorcode |= 0x0001;
    }
    else if (p_max == 0)
    {
        p_value = kp * p_value;
    }
    else
    {
        p_value = kp * p_value / p_max;
    }

    // Sum up the I term.
    // The error is multiplied by the time since the previous cycle.
    // I_Max = 0 means no limit or scaling.
    i_sum = i_sum + error * Time_Interval;
    i_sum = (i_sum > i_max) ? i_max : ((i_sum < -i_max) ? -i_max : i_sum);
    i_value = (i_max > 0) ? ki * i_sum / i_max : ((i_max == 0) ? i_sum : 0);

    if (Time_Interval <= 0)
    {
        i_value = 0;
        errorcode |= 0x0080;
    }
    else if (i_max < 0)
    {
        i_value = 0;
        errorcode |= 0x0002;
    }
    else if (i_max == 0)
    {
        i_value = ki * i_sum;
    }
    else
    {
        i_value = ki * i_sum / i_max;
    }

    // Calculate the D term.
    // Calculate the derivative of the point value.
    // A fading-memory filter is used.
    // Avoid a time interval of zero, which would cause division by zero.
    if (Time_Interval <= 0)
    {
        d_sum = 0;
        errorcode |= 0x0080;
    }
    else if (d_filter <= 0 || d_filter > 1)
    {
        d_sum = 0;
        errorcode |= 0x0004;
    }
    else
    {
        d_sum = d_sum * (1 - d_filter) + d_filter * (error - previous_error) / Time_Interval;
    }

    d_value = d_sum * kd;

    //------------------------------------------------------------------
    //                   Calculate final output.
    //------------------------------------------------------------------

    // Sum up terms and calculate final output.
    if (controlMode == PID_Calc::PID_Control_Mode::kPIDControlModePositionControl)
    {
        output = p_value + i_value - d_value;
    }
    else if (controlMode == PID_Calc::PID_Control_Mode::kPIDControlModeSpeedControl)
    {
        output = previous_output + p_value + i_value - d_value;
    }
    else
    {
        output = previous_output;
    }

    if (max_output < 0)
    {
        output = 0;
        errorcode |= 0x0008;
    }
    else if (max_output != 0)
    {
        output
        = (output > max_output) ? max_output : ((output < -max_output) ? -max_output : output);
    }

    if (accel_limit_high != 0 || accel_limit_low != 0)
    {
        output = (output > accel_limit_high)
                 ? accel_limit_high
                 : ((output < accel_limit_low) ? accel_limit_low : output);
    }

    //------------------------------------------------------------------
    //              Save data for future reference.
    //------------------------------------------------------------------

    if (Time_Interval <= 0)
    {
        settling_time = (error == 0) ? settling_time + 1.0 : 0;
        errorcode |= 0x0080;
    }
    else
    {
        settling_time = (error == 0) ? settling_time + Time_Interval : 0;
    }

    // Save data from this cycle.
    previous_error = error;
    previous_output = output;

    if (controlMode == PID_Calc::PID_Control_Mode::kPIDControlModeNoControl)
    {
        output = 0;
    }

    // Return output.
    return output;
}

// Tests whether or not the location has been within the desired range for the desired number of
// cycles.
bool PID_Calc::Is_Done(double Settling_Time)
{
    return settling_time > Settling_Time;
}

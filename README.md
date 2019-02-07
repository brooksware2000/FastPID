# FastPID
A fast 32-bit fixed-point PID controller for avr-gcc.

This is a port of Mike Materas's [FastPID](https://github.com/mike-matera/FastPID) project for Arduino.

## About 

This PID controller is faster than alternatives for Arduino because it avoids expensive floating point operations. The PID controller is configured with floating point coefficients and translates them to fixed point internally. This imposes limitations on the domain of the coefficients. Setting the I and D terms to zero makes the controller run faster. The controller is configured to run at a fixed frequency and calling code is responsible for running at that frequency. The `Ki` and `Kd` parameters are scaled by the frequency to save time during the `pid_step()` operation. 

## Description of Coefficients 

  * `Kp` - P term of the PID controller. 
  * `Ki` - I term of the PID controller. 
  * `Kd` - D term of the PID controller. 
  * `Hz` - The execution frequency of the controller. 

### Coefficient Domain 

The computation pipeline expects 16 bit coefficients. This is controlled by `PARAM_BITS` and should not be changed or caluclations may overflow. The number of bits before and after the decimal place is controlled by `PARAM_SHIFT` in `FastPID.h`. The default value for `PARAM_SHIFT` is 8 and can be changed to suit your application.

  * **The parameter P domain is [0.00390625 to 255] inclusive.** 
  * **The parameter I domain is P / Hz** 
  * **The parameter D domain is P * Hz** 

The controller checks for parameter domain violations and won't operate if a coefficient is outside of the range. All of the configuration operations return `bool` to alert the user of an error. The `pid_err()` function checks the error condition. Errors can be cleared with the `pid_clear()` function.

## Execution Frequency

**The execution frequency is not automatically detected as of version v1.1.0** This greatly improves the controller performance. Instead the `Ki` and `Kd` terms are scaled in the configuration step. It's essential to call `pid_step()` at the rate that you specify. 

## Input and Output 

The input and the setpoint are an `int16_t` this matches the width of Analog pins and accomodate negative readings and setpoints. The output of the PID is an `int16_t`. The actual bit-width and signedness of the output can be configured. 
  
  * `bits` - The output width will be limited to values inside of this bit range. Valid values are 1 through 16 
  * `sign` If `true` the output range is [-2^(bits-1), -2^(bits-1)-1]. If `false` output range is [0, 2^(bits-1)-1]. **The maximum output value of the controller is 32767 (even in 16 bit unsigned mode)** 

## Performance 

FastPID performance varies depending on the coefficients. When a coefficient is zero less calculation is done. The controller was benchmarked using an Arduino UNO and the code below. 

| Kp  | Ki  | Kd  | Step Time (uS) |
| --  | --  | --  | -------------- |
| 0.1 | 0.5 | 0.1 | ~64            |
| 0.1 | 0.5 | 0   | ~56            |
| 0.1 | 0   | 0   | ~28            |

For comparison the excellent [ArduinoPID](https://github.com/br3ttb/Arduino-PID-Library) library takes an average of about 90-100 uS per step with all non-zero coefficients. 

## API

See the separate [API documentation][api] for API details.

[api]: http://oddbit.com/FastPID/

## Tests & Examples

**NB**: The examples have not yet been ported over to work with avr-gcc.

There are some simple unit tests in the `test/` directory; you can run them like this:

    make -C test

The expected output will be something like:

    make: Entering directory '/home/lars/src/FastPID/test'
    test_pid_set_limits.ok
    test_pid_clear.ok
    test_pid_set_output.ok
    test_pid_step.ok
    test_pid_new.ok
    All tests passed.
    make: Leaving directory '/home/lars/src/FastPID/test'

The tests are defined in files named `test_<something>.c`.  The other files in the `test/` directory are from the upstream Arduino project and will not be useful with this code.

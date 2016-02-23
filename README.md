# PSoC3_TutorialSeries_PIDcontrol
Make an RC car travel at constant speed using a feedback loop via a Hall-effect sensor.


- **Hardware:**
  - Car chassis: Tamiya [TT02D](https://www.tamiyausa.com/product/item.php?product-id=47301) Type-S 
  - PSoC 3 DEV [kit](http://www.cypress.com/documentation/development-kitsboards/cy8ckit-030-psoc-3-development-kit)
  - DC motor: powering the RC car.
  - Hobby servo: for steering; to be used in a later tutorial for navigation and line following.
  - Hall effect sensor: [Allegro MicroSystems A1101](http://www.allegromicro.com/en/Products/Part_Numbers/1101/1101.pdf)
  - Power FET: For switching the motor. [datasheet](http://alltransistors.com/pdfdatasheet_motorola/mtp52n06vlrev3.pdf)

  In this project, the motor control board from the RC car kit is removed and the power delivered to the motor is controlled by a PWM signal from the PSoC. The car's speed feedback loop is read via a Hall effect sensor mounted on one of the wheels; counting ticks from permanent magnets fixed to the rim.

- **Software:**
  - Hall effect signal read by a GPIO pin
  - Global interrupts are handled by `main.c`
  - PWM signal from a GPIO digital output pin switches the FET.
  
  The timestamps are captured by a 32bit UDB timer every time the interrupt is called and the values are written to an array of size 2N, where N is the number of (fairly equally spaced) magnets on the wheel. By comparing the time difference between t[i+N] and t[N] the time-per-revolution is calculated. This value is further converted into speed by measuring the exact diameter of the wheel (assuming no drifting). The duty cycle of the PWM signal is then calculated based on the Error-signal (V_ref - V_current) and applied to the MOSFET gate through a digital GPIO.
  
The following diagram shows the project top design.

<img src="https://github.com/cvb0rg/PSoC3_TutorialSeries_PIDcontrol/blob/master/PSocTutorial_PID_control.png" alt="TopDesign.cysch file form the project">



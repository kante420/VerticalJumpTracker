# VerticalJumpTracker

The project involves the design and implementation of an electronic vertical jump tracking system that operates using the time-of-flight (TOF) measurement method. The primary objective is to accurately measure the height of a jump by calculating the total time the jumper spends in the air, from the moment both feet leave the ground until they return to contact.

The time-of-flight principle is based on the fact that, under constant gravitational acceleration, the duration of airborne movement directly correlates with the height reached. By precisely measuring this airborne time, the device can determine the vertical displacement of the jumper’s center of mass during the jump.

From the obtained time-of-flight values, the system will compute several key performance metrics:

    Jump Height (h): The maximum vertical distance achieved during the jump, calculated from the total flight time using kinematic equations.

    Take-off Velocity (v₀): The vertical component of the velocity at the exact instant the jumper leaves the ground. This is derived directly from the measured flight time and is a critical indicator of explosive leg power.

    Peak Power (Pₚₑₐₖ): The maximum instantaneous rate at which mechanical work is performed during the jump. It reflects the jumper’s ability to rapidly generate force and produce mechanical energy over time.

    Relative Peak Power (Pₚₑₐₖ / m): The peak power value normalized to the jumper’s body mass, providing a standardized measure of performance that allows comparisons between individuals of different weights.

This approach is particularly useful in sports science, physical conditioning, rehabilitation, and athlete monitoring, as it provides reliable, repeatable, and non-invasive measurements of lower-body explosive strength and power output.

Hardware Components to be integrated into the project include:

    Arduino Uno Microcontroller: The central processing unit responsible for reading sensor data, performing calculations, controlling outputs, and managing the user interface.

    VL53L0X Time-of-Flight Distance Sensor: A high-precision laser-based distance measurement module used to detect the vertical position of the jumper relative to the sensor. It enables accurate timing of take-off and landing events by detecting when the jumper leaves and recontacts the ground.

    LCD 16x2 Display with I²C Interface: A compact alphanumeric screen used to display detailed measurement results, such as flight time, jump height, take-off velocity, and power calculations, in a clear and readable format. The I²C interface simplifies wiring and reduces the number of required microcontroller pins.

    TM1637 4-Digit 7-Segment Display: A numerical display module that provides a quick and highly visible representation of selected values (e.g., jump height) for immediate feedback to the user.

    Push Button: A simple control input used to start a measurement session, reset stored data, or navigate between different display modes.

Once assembled, the device will operate in the following manner: the jumper positions themselves below the VL53L0X sensor and initiates the measurement using the push button. The system continuously monitors the distance between the sensor and the jumper. When the distance suddenly increases beyond a threshold (indicating take-off), the Arduino starts timing the flight. When the distance returns to its initial value (indicating landing), the flight time is recorded, and the calculations for height, velocity, and power are immediately performed. Results are then displayed both on the LCD 16x2 (for detailed readings) and the TM1637 7-segment display (for key numerical values).

The final product will provide athletes, coaches, and sports scientists with a compact, cost-effective, and precise tool for tracking performance, identifying areas for improvement, and monitoring progress over time.

<img width="1941" height="1596" alt="Untitled Sketch_bb" src="https://github.com/user-attachments/assets/a7316acf-4c02-451c-919c-8ba799042fbf" />

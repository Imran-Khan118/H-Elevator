# H-Elevator
This project demonstrates a lift model using Arduino, an LCD display, three push buttons, an H-bridge, and a DC encoder motor. The lift can move between three floors with real-time floor display and precise motor control using PID algorithms.

## Components Used

- **Arduino**
- **LiquidCrystal I2C LCD Display**
- **3 Push Buttons**
- **H-bridge** (made of two TLP250 and four MOSFET IRF640)
- **DC Encoder Motor**
- **Counterweight Mechanism** (for realistic lift operation)

## Features

- **Three Floors**: Ground floor, 1st floor, and 2nd floor.
- **Real-time Floor Display**: LCD shows the current floor.
- **Precise Motor Control**: Uses PID algorithm for smooth and accurate lift movement.
- **User Input**: Three push buttons to select target floors.

## Arduino Code

The code for controlling the lift is written in C++ using the Arduino framework. The main features of the code include reading encoder values, implementing a PID controller for motor control, and updating the LCD display with the current floor.

## How It Works

1. **Initialization**: The LCD and encoder are initialized, and the lift system displays an initial message on the LCD.
2. **Button Press**: When a button is pressed, the target floor is set accordingly.
3. **PID Control**: The PID controller calculates the required motor power and direction based on the encoder's current position and the target position.
4. **Motor Control**: The motor is driven in the appropriate direction with the calculated power to move the lift to the target floor.
5. **Display Update**: The current floor is continuously updated on the LCD display.



## Demonstration Video

Watch the lift model in action on YouTube:
[![Lift Model Video](https://img.youtube.com/vi/s2DexliY72Y/0.jpg)](https://youtu.be/s2DexliY72Y?si=x1JhmH9OFtQCrS_s)

## Usage

1. **Clone the repository**:
    ```sh
    git clone https://github.com/Imran-Khan118/H-Elevator.git
    ```
2. **Upload the Code**: Open the code in Arduino IDE and upload it to your Arduino board.
3. **Connect the Components**: Follow the wiring diagram to connect the components.
4. **Power the System**: Power up your system and use the push buttons to control the lift.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Special thanks to the Arduino community for providing helpful resources and libraries.

---

Feel free to contribute, report issues, or suggest improvements!

# Triggerbot by keww:L

## Description

This project is a simple triggerbot designed to automate mouse clicks based on pixel color changes in a game window. It utilizes the Windows API to interact with the game and performs actions based on the defined parameters.

## Features

- Detects significant pixel color changes.
- Automates mouse clicks in response to those changes.
- Customizable settings for various parameters.

## Requirements

- Windows operating system
- C++ compiler
- Necessary libraries for Windows API

## Usage

1. Compile the code using your preferred C++ compiler.
2. Run the executable.
3. Make sure the game window is active.
4. Press the designated key to activate the triggerbot.

## Usage 2

You can download the archive with the already assembled project and run the .exe file.

## Algorithm

The triggerbot algorithm works like this: the program constantly monitors the activity of the game window, checking whether it is active in the foreground. When the player presses a certain key, the triggerbot stores the colors of the pixels in the center of the screen, then compares the current pixels with the saved ones in a loop. If a significant color change is detected,
this indicates a change in the object in the center of the screen (for example, an enemy), and the program automatically performs a mouse click. The algorithm is also customizable according to the parameters of sensitivity, tracking radius and delay.

## Configuration:
- Radius: radius around the center of the screen where the area will be scanned, recommended value is 1px to 3px.
- Check delay: after how many ms it will scan the area, recommended value is 10 ms.
- Idle delay: doesn’t respond particularly well, you can set it to about 1000 ms.
- Color change threshold: color change threshold in percentage, how much should the color change in the scanning area for the triggerbot to work, the recommended value is from 10% to 25%.
- Activate key: which key the scanner will turn on.
- Game window title: name of the application window in which the triggerbot will work.

## Important Notice

This project is for educational purposes only. The creator does not take any responsibility for any actions taken with this software. Use at your own risk.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

- [GitHub](https://github.com/cbFelix/triggerbot)

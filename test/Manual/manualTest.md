# Manual Testing Instructions
## Setup
Set the pico up with another pico as the debugger and setup input for the system (either through uart or usb).
Flash hello_freertos.c using '''cmake --build build --target flash'''

## Input
Input the character 'a'. 

## Output 
The expected output is a single returned character: 'A'.

Additionally, the green LED will toggle on and off.
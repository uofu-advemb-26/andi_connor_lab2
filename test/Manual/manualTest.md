# Manual Testing Instructions
## Setup
Set the pico up with another pico as the debugger and setup input for the system (either through uart or usb).
Flash hello_freertos.c using '''cmake --build build --target flash'''

## Input
Input the character 'a'. 
Next, input the character 'B'.
Last, input a non-letter character: '$'

## Output 
The expected output will be an uppercase 'A', then a lowercase 'B', then '$'.

Additionally, the green LED will toggle on and off around 500 ms.
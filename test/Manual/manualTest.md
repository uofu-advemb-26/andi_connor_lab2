# Manual Testing Instructions
## Setup
1. Wire Pico A (running the debugprobe firmware) to Pico B:
   - Pico A pin 39 (VSYS) -> Pico B pin 39 (VSYS)
   - Pico A GND -> Pico B GND
   - Pico A GP2 -> Pico B SWCLK
   - Pico A GP3 -> Pico B SWDIO
   - Pico A GP4 (pin 6, TX) -> Pico B GP1 (pin 2, RX)
   - Pico A GP5 (pin 7, RX) -> Pico B GP0 (pin 1, TX)
2. Plug only Pico A into the computer over USB.
3. Make sure `src/CMakeLists.txt` has `pico_enable_stdio_uart(hello_freertos 1)` and `pico_enable_stdio_usb(hello_freertos 0)`.
4. Flash Pico B through the debugger: `cmake --build build --target openocd_flash`.
5. Open a serial terminal on the debugger's UART port:
   
## Input
Input the character 'a'.
Next, input the character 'B'.
Last, input a non-letter character: '$'

## Output
The expected output will be an uppercase 'A', then a lowercase 'b', then '$'.

Additionally, the green LED on Pico B will toggle on and off every 500 ms,
except that every 11th tick the toggle is skipped, so the LED holds the same
state for about 1 second once every ~5.5 seconds.

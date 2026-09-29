add_executable(mytest test.c unity_config.c)

# New unit tests for hello_freertos.c
add_executable(char_led_test char_led_test.c unity_config.c
  ${CMAKE_SOURCE_DIR}/src/refactored.c
)

# Linking also provides the include paths for <pico/stdlib.h> and <unity.h>.
target_link_libraries(char_led_test PRIVATE
  pico_stdlib
  unity
)

pico_enable_stdio_uart(char_led_test 1)
pico_enable_stdio_usb(char_led_test 0)

target_link_libraries(mytest PRIVATE
  pico_stdlib
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  unity
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    target_link_libraries(mytest PRIVATE
        pico_cyw43_arch_none
    )
endif()

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(mytest 1)
pico_enable_stdio_usb(mytest 0)

# This will speed up the simulation, since data won't be copied from the flash controller.
# It does make the binary non-persistent on a real microcontroller.
# pico_set_binary_type(mytest no_flash)

find_program(RENODE renode
# This is extra stuff so it can find the mac installation paths.
 NAMES macos_run.command Renode.exe
 PATHS /Applications/Renode.app/Contents/MacOS)

set(RENODE_FLAGS
  --disable-xwt
  --port -2
  --pid-file renode.pid
  --console
  )

add_test(NAME simulate_mytest COMMAND
    ${RENODE}
     ${RENODE_FLAGS}
    -e "$ELF=@$<TARGET_FILE:mytest>; $WORKING=@${CMAKE_SOURCE_DIR}; include @${CMAKE_SOURCE_DIR}/test/simulate.resc; start"
    )


find_program(OPENOCD openocd)
find_program(PICOTOOL picotool)

add_custom_target(flash_test ${PICOTOOL} load -f $<TARGET_FILE:mytest> DEPENDS mytest)
add_custom_target(openocd_test ${OPENOCD} -s ${OPENOCD_PATH} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c 'adapter speed 5000' -c 'program "$<TARGET_FILE:mytest>" verify reset exit' DEPENDS mytest)
add_custom_target(openocd_char_led_test ${OPENOCD} -s ${OPENOCD_PATH} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c 'adapter speed 5000' -c 'program "$<TARGET_FILE:char_led_test>" verify reset exit' DEPENDS char_led_test)

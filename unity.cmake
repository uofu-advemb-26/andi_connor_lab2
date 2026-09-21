# This sets up a library for Unity, they don't provide an importable cmake config.
add_library(unity ${UNITY_PATH}/src/unity.c
    include/hello_freertos.h)
target_include_directories(unity PUBLIC ${UNITY_PATH}/src)

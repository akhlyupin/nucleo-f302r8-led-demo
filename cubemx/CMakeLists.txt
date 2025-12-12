cmake_minimum_required(VERSION 3.22)

add_subdirectory(Drivers)

add_executable(nucleo-f302r8-ws2812
    # startup
    startup_stm32f302x8.s

    # base
    Core/Src/main.c
    Core/Src/stm32f3xx_hal_msp.c
    Core/Src/stm32f3xx_it.c
    $<$<CONFIG:Release>:Core/Src/syscalls.c>
    Core/Src/sysmem.c
    Core/Src/system_stm32f3xx.c

    # application
    Core/Src/application.cpp
    Core/Src/demo/demo.cpp
    Core/Src/demo/explosion.cpp
    Core/Src/demo/logo.cpp
    Core/Src/demo/player.cpp
    Core/Src/led/color.cpp
    Core/Src/led/display.cpp
    Core/Src/led/stripe.cpp
    Core/Src/led/ws2812.cpp
)

target_include_directories(nucleo-f302r8-ws2812 PRIVATE
    Core/Inc
    Core/Src
)

target_compile_definitions(nucleo-f302r8-ws2812 PRIVATE
)

target_compile_options(nucleo-f302r8-ws2812 PRIVATE 
    $<$<CONFIG:Debug>:-specs=rdimon.specs>
)

target_link_libraries(nucleo-f302r8-ws2812
    stm32-drivers

    $<$<CONFIG:Debug>:rdimon>
)

add_custom_command(TARGET nucleo-f302r8-ws2812 POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:nucleo-f302r8-ws2812> nucleo-f302r8-ws2812.hex
)

add_custom_command(TARGET nucleo-f302r8-ws2812 POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:nucleo-f302r8-ws2812> nucleo-f302r8-ws2812.bin
)

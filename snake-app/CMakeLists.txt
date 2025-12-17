cmake_minimum_required(VERSION 3.22)

add_executable(ws2812-snake-app
    snake_app.cpp
    
    game-engine/snake.cpp
    led/color.cpp
    led/display.cpp
    led/stripe.cpp
    led/ws2812.cpp
)

target_include_directories(ws2812-snake-app PRIVATE
    ./
)

target_compile_definitions(ws2812-snake-app PRIVATE
)

target_compile_options(ws2812-snake-app PRIVATE
    -Wall
    -Wpedantic
    -Wextra
    -Wshadow

    $<$<CONFIG:Debug>:-specs=rdimon.specs>
)

target_link_libraries(ws2812-snake-app
    stm32-drivers-headers
    nucleo-f302r8-cubemx

    $<$<CONFIG:Debug>:rdimon>
)

add_custom_command(TARGET ws2812-snake-app POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:ws2812-snake-app> ws2812-snake-app.hex
)

add_custom_command(TARGET ws2812-snake-app POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:ws2812-snake-app> ws2812-snake-app.bin
)

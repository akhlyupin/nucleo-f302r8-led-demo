cmake_minimum_required(VERSION 3.22)

add_subdirectory(Drivers)

add_library(nucleo-f302r8-cubemx OBJECT
    # startup
    startup_stm32f302x8.s

    # base
    Core/Src/main.c
    Core/Src/stm32f3xx_hal_msp.c
    Core/Src/stm32f3xx_it.c
    $<$<CONFIG:Release>:Core/Src/syscalls.c>
    Core/Src/sysmem.c
    Core/Src/system_stm32f3xx.c
)

target_include_directories(nucleo-f302r8-cubemx PUBLIC
    Core/Inc
    Core/Src
)

target_compile_definitions(nucleo-f302r8-cubemx PRIVATE
)

target_compile_options(nucleo-f302r8-cubemx PRIVATE
    $<$<CONFIG:Debug>:-specs=rdimon.specs>
)

target_link_libraries(nucleo-f302r8-cubemx PRIVATE
    stm32-drivers

    $<$<CONFIG:Debug>:rdimon>
)

cmake_minimum_required(VERSION 3.22)

add_library(stm32-drivers-headers INTERFACE)

target_compile_definitions(stm32-drivers-headers INTERFACE 
	USE_HAL_DRIVER 
	STM32F302x8
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(stm32-drivers-headers INTERFACE
    CMSIS/Include    
    CMSIS/Device/ST/STM32F3xx/Include
    STM32F3xx_HAL_Driver/Inc
    STM32F3xx_HAL_Driver/Inc/Legacy

    ${CMAKE_SOURCE_DIR}/cubemx/Core/Inc
)

add_library(stm32-drivers
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_exti.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim_ex.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c
    STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.c
)

target_link_libraries(stm32-drivers PUBLIC
    stm32-drivers-headers
)

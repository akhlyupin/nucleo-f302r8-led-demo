cmake_minimum_required(VERSION 3.22)

add_library(stm32-drivers INTERFACE)

enable_language(C ASM)

target_compile_definitions(stm32-drivers INTERFACE 
	USE_HAL_DRIVER 
	STM32F302x8
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(stm32-drivers INTERFACE
    CMSIS/Include    
    CMSIS/Device/ST/STM32F3xx/Include
    STM32F3xx_HAL_Driver/Inc
    STM32F3xx_HAL_Driver/Inc/Legacy

    ${CMAKE_SOURCE_DIR}/Core/Inc
)

target_sources(stm32-drivers INTERFACE
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

# Validate that stm32-drivers code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()



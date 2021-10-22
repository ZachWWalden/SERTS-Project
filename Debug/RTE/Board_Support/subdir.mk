################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/MDK/Boards/ST/STM32F4-Discovery/Common/Buttons_F4Discovery.c \
C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/MDK/Boards/ST/STM32F4-Discovery/Common/LED_F4Discovery.c 

OBJS += \
./RTE/Board_Support/Buttons_F4Discovery.o \
./RTE/Board_Support/LED_F4Discovery.o 

C_DEPS += \
./RTE/Board_Support/Buttons_F4Discovery.d \
./RTE/Board_Support/LED_F4Discovery.d 


# Each subdirectory must supply rules for building sources it contributes
RTE/Board_Support/Buttons_F4Discovery.o: C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/MDK/Boards/ST/STM32F4-Discovery/Common/Buttons_F4Discovery.c
	@echo 'Building file: $<'
	@echo 'Invoking: Arm C Compiler 6'
	armclang.exe --target=arm-arm-none-eabi -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mlittle-endian -DHSE_VALUE="8000000" -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM32F4_DISCO -DARM_MATH_CM4 -D_RTE_ -DSTM32F407xx -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/Core/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/DSP/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/DSP/PrivateInclude" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/Driver/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/RTOS/RTX/INC" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/RTOS/RTX/SRC/ARM" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/RTOS/RTX/UserCodeTemplates" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/MDK-Middleware/7.13.0/Board" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/MDK-Middleware/7.13.0/FileSystem/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/MDK-Middleware/7.13.0/USB/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/MDK/Device/Source/ARM" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/MDK/Templates/Inc" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/MDK/Templates_LL/Inc" -I"G:\SERTS\Sterlonkinator 9000 Workspace\SERTS-Project/RTE" -I"G:\SERTS\Sterlonkinator 9000 Workspace\SERTS-Project/RTE/Device/STM32F407VGTx" -I"G:\SERTS\Sterlonkinator 9000 Workspace\SERTS-Project/RTE/File_System" -I"G:\SERTS\Sterlonkinator 9000 Workspace\SERTS-Project/RTE/USB" -xc -std=c99 -O0 -g -fshort-enums -fshort-wchar -MD -MP -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Board_Support/LED_F4Discovery.o: C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/MDK/Boards/ST/STM32F4-Discovery/Common/LED_F4Discovery.c
	@echo 'Building file: $<'
	@echo 'Invoking: Arm C Compiler 6'
	armclang.exe --target=arm-arm-none-eabi -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mlittle-endian -DHSE_VALUE="8000000" -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM32F4_DISCO -DARM_MATH_CM4 -D_RTE_ -DSTM32F407xx -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/Core/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/DSP/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/DSP/PrivateInclude" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/Driver/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/RTOS/RTX/INC" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/RTOS/RTX/SRC/ARM" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/RTOS/RTX/UserCodeTemplates" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/MDK-Middleware/7.13.0/Board" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/MDK-Middleware/7.13.0/FileSystem/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/MDK-Middleware/7.13.0/USB/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/MDK/Device/Source/ARM" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/MDK/Templates/Inc" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/MDK/Templates_LL/Inc" -I"G:\SERTS\Sterlonkinator 9000 Workspace\SERTS-Project/RTE" -I"G:\SERTS\Sterlonkinator 9000 Workspace\SERTS-Project/RTE/Device/STM32F407VGTx" -I"G:\SERTS\Sterlonkinator 9000 Workspace\SERTS-Project/RTE/File_System" -I"G:\SERTS\Sterlonkinator 9000 Workspace\SERTS-Project/RTE/USB" -xc -std=c99 -O0 -g -fshort-enums -fshort-wchar -MD -MP -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



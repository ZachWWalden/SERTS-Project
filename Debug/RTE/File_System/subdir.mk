################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RTE/File_System/FS_Config.c 

OBJS += \
./RTE/File_System/FS_Config.o 

C_DEPS += \
./RTE/File_System/FS_Config.d 


# Each subdirectory must supply rules for building sources it contributes
RTE/File_System/%.o: ../RTE/File_System/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Arm C Compiler 6'
	armclang.exe --target=arm-arm-none-eabi -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mlittle-endian -DHSE_VALUE="8000000" -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM32F4_DISCO -DARM_MATH_CM4 -D_RTE_ -DSTM32F407xx -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/Core/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/DSP/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/DSP/PrivateInclude" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/Driver/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/RTOS/RTX/INC" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/RTOS/RTX/SRC/ARM" -I"C:/Users/Zach/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/RTOS/RTX/UserCodeTemplates" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/MDK-Middleware/7.13.0/Board" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/MDK-Middleware/7.13.0/FileSystem/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/MDK-Middleware/7.13.0/USB/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/MDK/Device/Source/ARM" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/MDK/Templates/Inc" -I"C:/Users/Zach/AppData/Local/Arm/Packs/Keil/STM32F4xx_DFP/2.15.0/MDK/Templates_LL/Inc" -I"G:\SERTS\SERTS Workspace\SERTS-Project/RTE" -I"G:\SERTS\SERTS Workspace\SERTS-Project/RTE/Device/STM32F407VGTx" -I"G:\SERTS\SERTS Workspace\SERTS-Project/RTE/File_System" -I"G:\SERTS\SERTS Workspace\SERTS-Project/RTE/USB" -xc -std=c99 -O0 -g -fshort-enums -fshort-wchar -MD -MP -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


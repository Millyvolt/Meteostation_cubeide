################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../CMSIS/Src/startup_stm32f103c8tx.s 

C_SRCS += \
../CMSIS/Src/system_stm32f1xx.c 

OBJS += \
./CMSIS/Src/startup_stm32f103c8tx.o \
./CMSIS/Src/system_stm32f1xx.o 

S_DEPS += \
./CMSIS/Src/startup_stm32f103c8tx.d 

C_DEPS += \
./CMSIS/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/Src/startup_stm32f103c8tx.o: ../CMSIS/Src/startup_stm32f103c8tx.s CMSIS/Src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -c -x assembler-with-cpp -MMD -MP -MF"CMSIS/Src/startup_stm32f103c8tx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
CMSIS/Src/system_stm32f1xx.o: ../CMSIS/Src/system_stm32f1xx.c CMSIS/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"C:/git_repos/meteostation/meteostation_tx/CMSIS/Inc" -I"C:/git_repos/meteostation/meteostation_tx/Drivers/Inc" -I"C:/git_repos/meteostation/meteostation_tx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CMSIS/Src/system_stm32f1xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


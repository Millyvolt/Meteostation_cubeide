################################################################################
# Automatically-generated file. Do not edit!
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
CMSIS/Src/startup_stm32f103c8tx.o: ../CMSIS/Src/startup_stm32f103c8tx.s
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -c -x assembler-with-cpp -MMD -MP -MF"CMSIS/Src/startup_stm32f103c8tx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
CMSIS/Src/system_stm32f1xx.o: ../CMSIS/Src/system_stm32f1xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"C:/git_repos/meteostation/meteostation_rx/CMSIS/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Drivers/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CMSIS/Src/system_stm32f1xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


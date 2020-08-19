################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/bme280.c \
../Drivers/Src/delay.c \
../Drivers/Src/fonts.c \
../Drivers/Src/hc_12.c \
../Drivers/Src/ssd1306.c \
../Drivers/Src/stm32_i2c.c \
../Drivers/Src/stm32_rcc.c \
../Drivers/Src/stm32_spi.c \
../Drivers/Src/stm32_usart.c \
../Drivers/Src/xprintf.c 

OBJS += \
./Drivers/Src/bme280.o \
./Drivers/Src/delay.o \
./Drivers/Src/fonts.o \
./Drivers/Src/hc_12.o \
./Drivers/Src/ssd1306.o \
./Drivers/Src/stm32_i2c.o \
./Drivers/Src/stm32_rcc.o \
./Drivers/Src/stm32_spi.o \
./Drivers/Src/stm32_usart.o \
./Drivers/Src/xprintf.o 

C_DEPS += \
./Drivers/Src/bme280.d \
./Drivers/Src/delay.d \
./Drivers/Src/fonts.d \
./Drivers/Src/hc_12.d \
./Drivers/Src/ssd1306.d \
./Drivers/Src/stm32_i2c.d \
./Drivers/Src/stm32_rcc.d \
./Drivers/Src/stm32_spi.d \
./Drivers/Src/stm32_usart.d \
./Drivers/Src/xprintf.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/bme280.o: ../Drivers/Src/bme280.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"C:/git_repos/meteostation/meteostation_rx/CMSIS/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Drivers/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Src/bme280.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/Src/delay.o: ../Drivers/Src/delay.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"C:/git_repos/meteostation/meteostation_rx/CMSIS/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Drivers/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Src/delay.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/Src/fonts.o: ../Drivers/Src/fonts.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"C:/git_repos/meteostation/meteostation_rx/CMSIS/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Drivers/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Src/fonts.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/Src/hc_12.o: ../Drivers/Src/hc_12.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"C:/git_repos/meteostation/meteostation_rx/CMSIS/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Drivers/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Src/hc_12.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/Src/ssd1306.o: ../Drivers/Src/ssd1306.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"C:/git_repos/meteostation/meteostation_rx/CMSIS/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Drivers/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Src/ssd1306.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/Src/stm32_i2c.o: ../Drivers/Src/stm32_i2c.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"C:/git_repos/meteostation/meteostation_rx/CMSIS/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Drivers/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Src/stm32_i2c.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/Src/stm32_rcc.o: ../Drivers/Src/stm32_rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"C:/git_repos/meteostation/meteostation_rx/CMSIS/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Drivers/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Src/stm32_rcc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/Src/stm32_spi.o: ../Drivers/Src/stm32_spi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"C:/git_repos/meteostation/meteostation_rx/CMSIS/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Drivers/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Src/stm32_spi.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/Src/stm32_usart.o: ../Drivers/Src/stm32_usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"C:/git_repos/meteostation/meteostation_rx/CMSIS/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Drivers/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Src/stm32_usart.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/Src/xprintf.o: ../Drivers/Src/xprintf.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"C:/git_repos/meteostation/meteostation_rx/CMSIS/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Drivers/Inc" -I"C:/git_repos/meteostation/meteostation_rx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Src/xprintf.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


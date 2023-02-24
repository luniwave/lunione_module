################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/Fonts/font12.c \
../Core/Inc/Fonts/font16.c \
../Core/Inc/Fonts/font20.c \
../Core/Inc/Fonts/font24.c \
../Core/Inc/Fonts/font8.c 

OBJS += \
./Core/Inc/Fonts/font12.o \
./Core/Inc/Fonts/font16.o \
./Core/Inc/Fonts/font20.o \
./Core/Inc/Fonts/font24.o \
./Core/Inc/Fonts/font8.o 

C_DEPS += \
./Core/Inc/Fonts/font12.d \
./Core/Inc/Fonts/font16.d \
./Core/Inc/Fonts/font20.d \
./Core/Inc/Fonts/font24.d \
./Core/Inc/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/Fonts/%.o Core/Inc/Fonts/%.su: ../Core/Inc/Fonts/%.c Core/Inc/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-Fonts

clean-Core-2f-Inc-2f-Fonts:
	-$(RM) ./Core/Inc/Fonts/font12.d ./Core/Inc/Fonts/font12.o ./Core/Inc/Fonts/font12.su ./Core/Inc/Fonts/font16.d ./Core/Inc/Fonts/font16.o ./Core/Inc/Fonts/font16.su ./Core/Inc/Fonts/font20.d ./Core/Inc/Fonts/font20.o ./Core/Inc/Fonts/font20.su ./Core/Inc/Fonts/font24.d ./Core/Inc/Fonts/font24.o ./Core/Inc/Fonts/font24.su ./Core/Inc/Fonts/font8.d ./Core/Inc/Fonts/font8.o ./Core/Inc/Fonts/font8.su

.PHONY: clean-Core-2f-Inc-2f-Fonts


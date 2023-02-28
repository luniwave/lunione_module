################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/GUI/GUI_BMPfile.c \
../Core/Inc/GUI/GUI_Paint.c 

OBJS += \
./Core/Inc/GUI/GUI_BMPfile.o \
./Core/Inc/GUI/GUI_Paint.o 

C_DEPS += \
./Core/Inc/GUI/GUI_BMPfile.d \
./Core/Inc/GUI/GUI_Paint.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/GUI/%.o Core/Inc/GUI/%.su: ../Core/Inc/GUI/%.c Core/Inc/GUI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../STM32_WPAN/App -I../Utilities/lpm/tiny_lpm -I../Middlewares/ST/STM32_WPAN -I../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../Middlewares/ST/STM32_WPAN/utilities -I../Middlewares/ST/STM32_WPAN/ble/core -I../Middlewares/ST/STM32_WPAN/ble/core/auto -I../Middlewares/ST/STM32_WPAN/ble/core/template -I../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../Utilities/sequencer -I../Middlewares/ST/STM32_WPAN/ble -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-GUI

clean-Core-2f-Inc-2f-GUI:
	-$(RM) ./Core/Inc/GUI/GUI_BMPfile.d ./Core/Inc/GUI/GUI_BMPfile.o ./Core/Inc/GUI/GUI_BMPfile.su ./Core/Inc/GUI/GUI_Paint.d ./Core/Inc/GUI/GUI_Paint.o ./Core/Inc/GUI/GUI_Paint.su

.PHONY: clean-Core-2f-Inc-2f-GUI


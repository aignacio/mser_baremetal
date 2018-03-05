################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/utils/alt_p2uart.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/utils/alt_printf.c 

OBJS += \
./src_lib/utils/alt_p2uart.o \
./src_lib/utils/alt_printf.o 

C_DEPS += \
./src_lib/utils/alt_p2uart.d \
./src_lib/utils/alt_printf.d 


# Each subdirectory must supply rules for building sources it contributes
src_lib/utils/alt_p2uart.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/utils/alt_p2uart.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_lib/utils/alt_printf.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/utils/alt_printf.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



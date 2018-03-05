################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/io.c \
../src/main.c \
../src/mser.c \
../src/system_crios.c 

OBJS += \
./src/io.o \
./src/main.o \
./src/mser.o \
./src/system_crios.o 

C_DEPS += \
./src/io.d \
./src/main.d \
./src/mser.d \
./src/system_crios.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



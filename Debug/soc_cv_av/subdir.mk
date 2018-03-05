################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_bridge_manager.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_clock_manager.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_clock_manager_init.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_ecc.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_fpga_manager.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_reset_manager.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_sdram.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_system_manager.c 

OBJS += \
./soc_cv_av/alt_bridge_manager.o \
./soc_cv_av/alt_clock_manager.o \
./soc_cv_av/alt_clock_manager_init.o \
./soc_cv_av/alt_ecc.o \
./soc_cv_av/alt_fpga_manager.o \
./soc_cv_av/alt_reset_manager.o \
./soc_cv_av/alt_sdram.o \
./soc_cv_av/alt_system_manager.o 

C_DEPS += \
./soc_cv_av/alt_bridge_manager.d \
./soc_cv_av/alt_clock_manager.d \
./soc_cv_av/alt_clock_manager_init.d \
./soc_cv_av/alt_ecc.d \
./soc_cv_av/alt_fpga_manager.d \
./soc_cv_av/alt_reset_manager.d \
./soc_cv_av/alt_sdram.d \
./soc_cv_av/alt_system_manager.d 


# Each subdirectory must supply rules for building sources it contributes
soc_cv_av/alt_bridge_manager.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_bridge_manager.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	arm-altera-eabi-gcc -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

soc_cv_av/alt_clock_manager.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_clock_manager.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	arm-altera-eabi-gcc -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

soc_cv_av/alt_clock_manager_init.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_clock_manager_init.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	arm-altera-eabi-gcc -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

soc_cv_av/alt_ecc.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_ecc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	arm-altera-eabi-gcc -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

soc_cv_av/alt_fpga_manager.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_fpga_manager.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	arm-altera-eabi-gcc -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

soc_cv_av/alt_reset_manager.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_reset_manager.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	arm-altera-eabi-gcc -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

soc_cv_av/alt_sdram.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_sdram.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	arm-altera-eabi-gcc -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

soc_cv_av/alt_system_manager.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/soc_cv_av/alt_system_manager.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	arm-altera-eabi-gcc -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



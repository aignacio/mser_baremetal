################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_16550_uart.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_address_space.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_cache.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_can.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_dma.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_dma_program.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_generalpurpose_io.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_globaltmr.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_i2c.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_interrupt.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_mmu.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_nand.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_qspi.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_sdmmc.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_spi.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_timers.c \
C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_watchdog.c 

OBJS += \
./src_libs_add/hwmgr/alt_16550_uart.o \
./src_libs_add/hwmgr/alt_address_space.o \
./src_libs_add/hwmgr/alt_cache.o \
./src_libs_add/hwmgr/alt_can.o \
./src_libs_add/hwmgr/alt_dma.o \
./src_libs_add/hwmgr/alt_dma_program.o \
./src_libs_add/hwmgr/alt_generalpurpose_io.o \
./src_libs_add/hwmgr/alt_globaltmr.o \
./src_libs_add/hwmgr/alt_i2c.o \
./src_libs_add/hwmgr/alt_interrupt.o \
./src_libs_add/hwmgr/alt_mmu.o \
./src_libs_add/hwmgr/alt_nand.o \
./src_libs_add/hwmgr/alt_qspi.o \
./src_libs_add/hwmgr/alt_sdmmc.o \
./src_libs_add/hwmgr/alt_spi.o \
./src_libs_add/hwmgr/alt_timers.o \
./src_libs_add/hwmgr/alt_watchdog.o 

C_DEPS += \
./src_libs_add/hwmgr/alt_16550_uart.d \
./src_libs_add/hwmgr/alt_address_space.d \
./src_libs_add/hwmgr/alt_cache.d \
./src_libs_add/hwmgr/alt_can.d \
./src_libs_add/hwmgr/alt_dma.d \
./src_libs_add/hwmgr/alt_dma_program.d \
./src_libs_add/hwmgr/alt_generalpurpose_io.d \
./src_libs_add/hwmgr/alt_globaltmr.d \
./src_libs_add/hwmgr/alt_i2c.d \
./src_libs_add/hwmgr/alt_interrupt.d \
./src_libs_add/hwmgr/alt_mmu.d \
./src_libs_add/hwmgr/alt_nand.d \
./src_libs_add/hwmgr/alt_qspi.d \
./src_libs_add/hwmgr/alt_sdmmc.d \
./src_libs_add/hwmgr/alt_spi.d \
./src_libs_add/hwmgr/alt_timers.d \
./src_libs_add/hwmgr/alt_watchdog.d 


# Each subdirectory must supply rules for building sources it contributes
src_libs_add/hwmgr/alt_16550_uart.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_16550_uart.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_address_space.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_address_space.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_cache.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_cache.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_can.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_can.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_dma.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_dma.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_dma_program.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_dma_program.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_generalpurpose_io.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_generalpurpose_io.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_globaltmr.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_globaltmr.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_i2c.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_interrupt.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_interrupt.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_mmu.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_mmu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_nand.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_nand.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_qspi.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_qspi.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_sdmmc.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_sdmmc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_spi.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_timers.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_timers.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_libs_add/hwmgr/alt_watchdog.o: C:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/src/hwmgr/alt_watchdog.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -march=armv7-a -Dsoc_cv_av -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib" -I"C:\intelFPGA\17.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



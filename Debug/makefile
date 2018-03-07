################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := clean

# All of the sources participating in the build are defined here
-include sources.mk
-include src_libs_add/utils/subdir.mk
-include src_libs_add/hwmgr/soc_cv_av/subdir.mk
-include src_libs_add/hwmgr/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: CRIOS_ARM.axf

# Tool invocations
CRIOS_ARM.axf: $(OBJS) C:\Users\aignacio\Documents\DS-5\ Workspace\CRIOS_ARM\cycloneV-dk-ram-hosted.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker 6.2.0 [arm-altera-eabi]'
	arm-altera-eabi-gcc.exe -T "C:\Users\aignacio\Documents\DS-5 Workspace\CRIOS_ARM\cycloneV-dk-ram-hosted.ld" -o "CRIOS_ARM.axf" $(OBJS) $(LIBS) $(USER_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS) $(C_DEPS) $(EXECUTABLES) CRIOS_ARM.axf 
	-@echo ' '

post-build:
	-@echo 'Generate the binary file for the application'
	-arm-altera-eabi-objcopy -O binary CRIOS_ARM.axf baremetal.bin
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

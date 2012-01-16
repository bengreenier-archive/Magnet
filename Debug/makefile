################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include overlay/subdir.mk
-include mgui/subdir.mk
-include World/Storage/subdir.mk
-include World/Stats/subdir.mk
-include World/Shapes/subdir.mk
-include World/Material/subdir.mk
-include World/subdir.mk
-include Player/Bases/subdir.mk
-include Player/subdir.mk
-include Movement/subdir.mk
-include Gun/subdir.mk
-include Game/Resource/subdir.mk
-include Game/Handlers/subdir.mk
-include Game/subdir.mk
-include FileActions/subdir.mk
-include Conversions/subdir.mk
-include Console/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Magnet

# Tool invocations
Magnet: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++  -o "Magnet" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) Magnet
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

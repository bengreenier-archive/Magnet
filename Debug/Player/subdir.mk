################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Player/Inventory.cpp \
../Player/Player.cpp \
../Player/Selected.cpp 

OBJS += \
./Player/Inventory.o \
./Player/Player.o \
./Player/Selected.o 

CPP_DEPS += \
./Player/Inventory.d \
./Player/Player.d \
./Player/Selected.d 


# Each subdirectory must supply rules for building sources it contributes
Player/%.o: ../Player/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Projects\Magnet\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



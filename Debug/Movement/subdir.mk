################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Movement/MovementBase.cpp \
../Movement/UserControlled.cpp 

OBJS += \
./Movement/MovementBase.o \
./Movement/UserControlled.o 

CPP_DEPS += \
./Movement/MovementBase.d \
./Movement/UserControlled.d 


# Each subdirectory must supply rules for building sources it contributes
Movement/%.o: ../Movement/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Projects\Magnet\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



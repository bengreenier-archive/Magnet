################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../mgui/Component.cpp \
../mgui/Group.cpp \
../mgui/Positionable.cpp \
../mgui/Registry.cpp 

OBJS += \
./mgui/Component.o \
./mgui/Group.o \
./mgui/Positionable.o \
./mgui/Registry.o 

CPP_DEPS += \
./mgui/Component.d \
./mgui/Group.d \
./mgui/Positionable.d \
./mgui/Registry.d 


# Each subdirectory must supply rules for building sources it contributes
mgui/%.o: ../mgui/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Projects\Magnet\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



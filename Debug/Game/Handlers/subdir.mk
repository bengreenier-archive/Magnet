################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Game/Handlers/EventHandler.cpp \
../Game/Handlers/FontHandler.cpp \
../Game/Handlers/ImageHandler.cpp 

OBJS += \
./Game/Handlers/EventHandler.o \
./Game/Handlers/FontHandler.o \
./Game/Handlers/ImageHandler.o 

CPP_DEPS += \
./Game/Handlers/EventHandler.d \
./Game/Handlers/FontHandler.d \
./Game/Handlers/ImageHandler.d 


# Each subdirectory must supply rules for building sources it contributes
Game/Handlers/%.o: ../Game/Handlers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Projects\Magnet\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



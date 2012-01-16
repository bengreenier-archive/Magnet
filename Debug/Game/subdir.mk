################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../Game/MouseTrail.o 

CPP_SRCS += \
../Game/Callback.cpp \
../Game/EventListener.cpp \
../Game/MouseTrail.cpp \
../Game/Renderer.cpp \
../Game/Resource.cpp \
../Game/TrailCircle.cpp 

OBJS += \
./Game/Callback.o \
./Game/EventListener.o \
./Game/MouseTrail.o \
./Game/Renderer.o \
./Game/Resource.o \
./Game/TrailCircle.o 

CPP_DEPS += \
./Game/Callback.d \
./Game/EventListener.d \
./Game/MouseTrail.d \
./Game/Renderer.d \
./Game/Resource.d \
./Game/TrailCircle.d 


# Each subdirectory must supply rules for building sources it contributes
Game/%.o: ../Game/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Projects\Magnet\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



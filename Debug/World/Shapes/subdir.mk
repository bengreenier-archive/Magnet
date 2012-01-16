################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../World/Shapes/Circle.cpp \
../World/Shapes/PhysShape.cpp \
../World/Shapes/Rect.cpp 

OBJS += \
./World/Shapes/Circle.o \
./World/Shapes/PhysShape.o \
./World/Shapes/Rect.o 

CPP_DEPS += \
./World/Shapes/Circle.d \
./World/Shapes/PhysShape.d \
./World/Shapes/Rect.d 


# Each subdirectory must supply rules for building sources it contributes
World/Shapes/%.o: ../World/Shapes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Projects\Magnet\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Console/Console.cpp \
../Console/ConsoleThread.cpp \
../Console/FunctionPtrTemplate.cpp 

OBJS += \
./Console/Console.o \
./Console/ConsoleThread.o \
./Console/FunctionPtrTemplate.o 

CPP_DEPS += \
./Console/Console.d \
./Console/ConsoleThread.d \
./Console/FunctionPtrTemplate.d 


# Each subdirectory must supply rules for building sources it contributes
Console/%.o: ../Console/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Projects\Magnet\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



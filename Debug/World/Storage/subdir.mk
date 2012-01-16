################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../World/Storage/WorldStorage.cpp 

OBJS += \
./World/Storage/WorldStorage.o 

CPP_DEPS += \
./World/Storage/WorldStorage.d 


# Each subdirectory must supply rules for building sources it contributes
World/Storage/%.o: ../World/Storage/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Projects\Magnet\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



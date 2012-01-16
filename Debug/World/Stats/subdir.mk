################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../World/Stats/WorldStats.cpp 

OBJS += \
./World/Stats/WorldStats.o 

CPP_DEPS += \
./World/Stats/WorldStats.d 


# Each subdirectory must supply rules for building sources it contributes
World/Stats/%.o: ../World/Stats/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Projects\Magnet\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



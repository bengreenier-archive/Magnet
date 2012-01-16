################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../overlay/overlay.cpp \
../overlay/overlayController.cpp 

OBJS += \
./overlay/overlay.o \
./overlay/overlayController.o 

CPP_DEPS += \
./overlay/overlay.d \
./overlay/overlayController.d 


# Each subdirectory must supply rules for building sources it contributes
overlay/%.o: ../overlay/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Projects\Magnet\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



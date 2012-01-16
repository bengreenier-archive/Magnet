################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Player/Bases/Apparel.cpp \
../Player/Bases/ItemBase.cpp \
../Player/Bases/Misc.cpp \
../Player/Bases/Weapon.cpp 

OBJS += \
./Player/Bases/Apparel.o \
./Player/Bases/ItemBase.o \
./Player/Bases/Misc.o \
./Player/Bases/Weapon.o 

CPP_DEPS += \
./Player/Bases/Apparel.d \
./Player/Bases/ItemBase.d \
./Player/Bases/Misc.d \
./Player/Bases/Weapon.d 


# Each subdirectory must supply rules for building sources it contributes
Player/Bases/%.o: ../Player/Bases/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Projects\Magnet\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



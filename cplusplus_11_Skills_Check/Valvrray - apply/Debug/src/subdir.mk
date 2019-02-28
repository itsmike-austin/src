################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Valvrray\ -\ apply.cpp 

OBJS += \
./src/Valvrray\ -\ apply.o 

CPP_DEPS += \
./src/Valvrray\ -\ apply.d 


# Each subdirectory must supply rules for building sources it contributes
src/Valvrray\ -\ apply.o: ../src/Valvrray\ -\ apply.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Valvrray - apply.d" -MT"src/Valvrray\ -\ apply.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



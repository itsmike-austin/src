################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Utility\ -\ swap.cpp 

OBJS += \
./src/Utility\ -\ swap.o 

CPP_DEPS += \
./src/Utility\ -\ swap.d 


# Each subdirectory must supply rules for building sources it contributes
src/Utility\ -\ swap.o: ../src/Utility\ -\ swap.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Utility - swap.d" -MT"src/Utility\ -\ swap.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



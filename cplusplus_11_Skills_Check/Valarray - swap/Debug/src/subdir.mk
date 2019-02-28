################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Valarray\ -\ swap.cpp 

OBJS += \
./src/Valarray\ -\ swap.o 

CPP_DEPS += \
./src/Valarray\ -\ swap.d 


# Each subdirectory must supply rules for building sources it contributes
src/Valarray\ -\ swap.o: ../src/Valarray\ -\ swap.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Valarray - swap.d" -MT"src/Valarray\ -\ swap.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



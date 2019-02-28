################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Valvarray\ -\ operators.cpp 

OBJS += \
./src/Valvarray\ -\ operators.o 

CPP_DEPS += \
./src/Valvarray\ -\ operators.d 


# Each subdirectory must supply rules for building sources it contributes
src/Valvarray\ -\ operators.o: ../src/Valvarray\ -\ operators.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Valvarray - operators.d" -MT"src/Valvarray\ -\ operators.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



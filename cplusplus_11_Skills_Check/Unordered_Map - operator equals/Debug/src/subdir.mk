################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Unordered_Map\ -\ operator\ equals.cpp 

OBJS += \
./src/Unordered_Map\ -\ operator\ equals.o 

CPP_DEPS += \
./src/Unordered_Map\ -\ operator\ equals.d 


# Each subdirectory must supply rules for building sources it contributes
src/Unordered_Map\ -\ operator\ equals.o: ../src/Unordered_Map\ -\ operator\ equals.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Unordered_Map - operator equals.d" -MT"src/Unordered_Map\ -\ operator\ equals.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



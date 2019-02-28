################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ operator\ equals.cpp 

OBJS += \
./src/Vector\ -\ operator\ equals.o 

CPP_DEPS += \
./src/Vector\ -\ operator\ equals.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ operator\ equals.o: ../src/Vector\ -\ operator\ equals.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - operator equals.d" -MT"src/Vector\ -\ operator\ equals.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



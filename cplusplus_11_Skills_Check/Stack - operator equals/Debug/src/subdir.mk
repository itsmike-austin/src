################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Stack\ -\ operator\ equals.cpp 

OBJS += \
./src/Stack\ -\ operator\ equals.o 

CPP_DEPS += \
./src/Stack\ -\ operator\ equals.d 


# Each subdirectory must supply rules for building sources it contributes
src/Stack\ -\ operator\ equals.o: ../src/Stack\ -\ operator\ equals.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Stack - operator equals.d" -MT"src/Stack\ -\ operator\ equals.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



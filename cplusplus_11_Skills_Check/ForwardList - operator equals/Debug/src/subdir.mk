################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ForwardList\ -\ operator\ equals.cpp 

OBJS += \
./src/ForwardList\ -\ operator\ equals.o 

CPP_DEPS += \
./src/ForwardList\ -\ operator\ equals.d 


# Each subdirectory must supply rules for building sources it contributes
src/ForwardList\ -\ operator\ equals.o: ../src/ForwardList\ -\ operator\ equals.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/ForwardList - operator equals.d" -MT"src/ForwardList\ -\ operator\ equals.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ForwardList\ -\ reverse.cpp 

OBJS += \
./src/ForwardList\ -\ reverse.o 

CPP_DEPS += \
./src/ForwardList\ -\ reverse.d 


# Each subdirectory must supply rules for building sources it contributes
src/ForwardList\ -\ reverse.o: ../src/ForwardList\ -\ reverse.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/ForwardList - reverse.d" -MT"src/ForwardList\ -\ reverse.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



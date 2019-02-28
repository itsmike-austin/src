################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ForwardList\ -\ swap.cpp 

OBJS += \
./src/ForwardList\ -\ swap.o 

CPP_DEPS += \
./src/ForwardList\ -\ swap.d 


# Each subdirectory must supply rules for building sources it contributes
src/ForwardList\ -\ swap.o: ../src/ForwardList\ -\ swap.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/ForwardList - swap.d" -MT"src/ForwardList\ -\ swap.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



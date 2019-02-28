################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ swap.cpp 

OBJS += \
./src/Deque\ -\ swap.o 

CPP_DEPS += \
./src/Deque\ -\ swap.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ swap.o: ../src/Deque\ -\ swap.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - swap.d" -MT"src/Deque\ -\ swap.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



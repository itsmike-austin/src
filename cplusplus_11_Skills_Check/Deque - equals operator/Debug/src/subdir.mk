################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ equals\ operator.cpp 

OBJS += \
./src/Deque\ -\ equals\ operator.o 

CPP_DEPS += \
./src/Deque\ -\ equals\ operator.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ equals\ operator.o: ../src/Deque\ -\ equals\ operator.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - equals operator.d" -MT"src/Deque\ -\ equals\ operator.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



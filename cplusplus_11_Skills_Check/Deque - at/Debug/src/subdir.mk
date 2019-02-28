################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ at.cpp 

OBJS += \
./src/Deque\ -\ at.o 

CPP_DEPS += \
./src/Deque\ -\ at.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ at.o: ../src/Deque\ -\ at.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - at.d" -MT"src/Deque\ -\ at.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



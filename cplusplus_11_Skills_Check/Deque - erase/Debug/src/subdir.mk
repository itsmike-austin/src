################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ erase.cpp 

OBJS += \
./src/Deque\ -\ erase.o 

CPP_DEPS += \
./src/Deque\ -\ erase.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ erase.o: ../src/Deque\ -\ erase.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - erase.d" -MT"src/Deque\ -\ erase.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



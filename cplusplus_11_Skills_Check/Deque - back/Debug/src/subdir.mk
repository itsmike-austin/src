################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ back.cpp 

OBJS += \
./src/Deque\ -\ back.o 

CPP_DEPS += \
./src/Deque\ -\ back.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ back.o: ../src/Deque\ -\ back.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - back.d" -MT"src/Deque\ -\ back.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



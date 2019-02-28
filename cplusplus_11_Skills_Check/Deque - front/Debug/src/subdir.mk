################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ front.cpp 

OBJS += \
./src/Deque\ -\ front.o 

CPP_DEPS += \
./src/Deque\ -\ front.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ front.o: ../src/Deque\ -\ front.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - front.d" -MT"src/Deque\ -\ front.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ pop_back.cpp 

OBJS += \
./src/Deque\ -\ pop_back.o 

CPP_DEPS += \
./src/Deque\ -\ pop_back.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ pop_back.o: ../src/Deque\ -\ pop_back.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - pop_back.d" -MT"src/Deque\ -\ pop_back.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


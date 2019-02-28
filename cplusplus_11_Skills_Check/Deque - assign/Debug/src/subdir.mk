################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ assign.cpp 

OBJS += \
./src/Deque\ -\ assign.o 

CPP_DEPS += \
./src/Deque\ -\ assign.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ assign.o: ../src/Deque\ -\ assign.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - assign.d" -MT"src/Deque\ -\ assign.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



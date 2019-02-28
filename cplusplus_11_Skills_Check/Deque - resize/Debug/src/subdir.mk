################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ resize.cpp 

OBJS += \
./src/Deque\ -\ resize.o 

CPP_DEPS += \
./src/Deque\ -\ resize.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ resize.o: ../src/Deque\ -\ resize.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - resize.d" -MT"src/Deque\ -\ resize.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



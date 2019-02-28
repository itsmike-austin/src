################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ clear.cpp 

OBJS += \
./src/Deque\ -\ clear.o 

CPP_DEPS += \
./src/Deque\ -\ clear.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ clear.o: ../src/Deque\ -\ clear.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - clear.d" -MT"src/Deque\ -\ clear.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



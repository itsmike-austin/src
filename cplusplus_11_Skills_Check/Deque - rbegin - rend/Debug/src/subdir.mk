################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ rbegin\ -\ rend.cpp 

OBJS += \
./src/Deque\ -\ rbegin\ -\ rend.o 

CPP_DEPS += \
./src/Deque\ -\ rbegin\ -\ rend.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ rbegin\ -\ rend.o: ../src/Deque\ -\ rbegin\ -\ rend.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - rbegin - rend.d" -MT"src/Deque\ -\ rbegin\ -\ rend.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



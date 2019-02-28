################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ cbegin\ -\ cend.cpp 

OBJS += \
./src/Deque\ -\ cbegin\ -\ cend.o 

CPP_DEPS += \
./src/Deque\ -\ cbegin\ -\ cend.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ cbegin\ -\ cend.o: ../src/Deque\ -\ cbegin\ -\ cend.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - cbegin - cend.d" -MT"src/Deque\ -\ cbegin\ -\ cend.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



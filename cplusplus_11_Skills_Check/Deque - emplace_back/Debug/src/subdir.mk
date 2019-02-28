################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ emplace_back.cpp 

OBJS += \
./src/Deque\ -\ emplace_back.o 

CPP_DEPS += \
./src/Deque\ -\ emplace_back.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ emplace_back.o: ../src/Deque\ -\ emplace_back.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - emplace_back.d" -MT"src/Deque\ -\ emplace_back.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



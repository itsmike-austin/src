################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ emplace.cpp 

OBJS += \
./src/Deque\ -\ emplace.o 

CPP_DEPS += \
./src/Deque\ -\ emplace.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ emplace.o: ../src/Deque\ -\ emplace.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - emplace.d" -MT"src/Deque\ -\ emplace.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



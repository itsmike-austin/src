################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ get_allocator.cpp 

OBJS += \
./src/Deque\ -\ get_allocator.o 

CPP_DEPS += \
./src/Deque\ -\ get_allocator.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ get_allocator.o: ../src/Deque\ -\ get_allocator.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - get_allocator.d" -MT"src/Deque\ -\ get_allocator.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



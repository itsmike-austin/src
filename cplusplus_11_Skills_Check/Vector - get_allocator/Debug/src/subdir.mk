################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ get_allocator.cpp 

OBJS += \
./src/Vector\ -\ get_allocator.o 

CPP_DEPS += \
./src/Vector\ -\ get_allocator.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ get_allocator.o: ../src/Vector\ -\ get_allocator.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - get_allocator.d" -MT"src/Vector\ -\ get_allocator.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


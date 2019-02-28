################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ operator\ square\ braces.cpp 

OBJS += \
./src/Deque\ -\ operator\ square\ braces.o 

CPP_DEPS += \
./src/Deque\ -\ operator\ square\ braces.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ operator\ square\ braces.o: ../src/Deque\ -\ operator\ square\ braces.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - operator square braces.d" -MT"src/Deque\ -\ operator\ square\ braces.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



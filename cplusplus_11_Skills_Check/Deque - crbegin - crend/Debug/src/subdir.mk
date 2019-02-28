################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ crbegin\ -\ crend.cpp 

OBJS += \
./src/Deque\ -\ crbegin\ -\ crend.o 

CPP_DEPS += \
./src/Deque\ -\ crbegin\ -\ crend.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ crbegin\ -\ crend.o: ../src/Deque\ -\ crbegin\ -\ crend.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - crbegin - crend.d" -MT"src/Deque\ -\ crbegin\ -\ crend.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



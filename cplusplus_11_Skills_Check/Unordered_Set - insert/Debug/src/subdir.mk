################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Unordered_Set\ -\ insert.cpp 

OBJS += \
./src/Unordered_Set\ -\ insert.o 

CPP_DEPS += \
./src/Unordered_Set\ -\ insert.d 


# Each subdirectory must supply rules for building sources it contributes
src/Unordered_Set\ -\ insert.o: ../src/Unordered_Set\ -\ insert.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Unordered_Set - insert.d" -MT"src/Unordered_Set\ -\ insert.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



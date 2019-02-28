################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Valarray\ -\ shift.cpp 

OBJS += \
./src/Valarray\ -\ shift.o 

CPP_DEPS += \
./src/Valarray\ -\ shift.d 


# Each subdirectory must supply rules for building sources it contributes
src/Valarray\ -\ shift.o: ../src/Valarray\ -\ shift.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Valarray - shift.d" -MT"src/Valarray\ -\ shift.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



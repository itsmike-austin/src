################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Valarray\ -\ cshift.cpp 

OBJS += \
./src/Valarray\ -\ cshift.o 

CPP_DEPS += \
./src/Valarray\ -\ cshift.d 


# Each subdirectory must supply rules for building sources it contributes
src/Valarray\ -\ cshift.o: ../src/Valarray\ -\ cshift.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Valarray - cshift.d" -MT"src/Valarray\ -\ cshift.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



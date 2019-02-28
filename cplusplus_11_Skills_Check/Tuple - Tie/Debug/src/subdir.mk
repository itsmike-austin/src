################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Tuple\ -\ Tie.cpp 

OBJS += \
./src/Tuple\ -\ Tie.o 

CPP_DEPS += \
./src/Tuple\ -\ Tie.d 


# Each subdirectory must supply rules for building sources it contributes
src/Tuple\ -\ Tie.o: ../src/Tuple\ -\ Tie.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Tuple - Tie.d" -MT"src/Tuple\ -\ Tie.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



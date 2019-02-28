################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Tuple\ -\ Make.cpp 

OBJS += \
./src/Tuple\ -\ Make.o 

CPP_DEPS += \
./src/Tuple\ -\ Make.d 


# Each subdirectory must supply rules for building sources it contributes
src/Tuple\ -\ Make.o: ../src/Tuple\ -\ Make.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Tuple - Make.d" -MT"src/Tuple\ -\ Make.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



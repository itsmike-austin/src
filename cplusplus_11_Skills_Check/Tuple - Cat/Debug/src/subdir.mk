################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Tuple\ -\ Cat.cpp 

OBJS += \
./src/Tuple\ -\ Cat.o 

CPP_DEPS += \
./src/Tuple\ -\ Cat.d 


# Each subdirectory must supply rules for building sources it contributes
src/Tuple\ -\ Cat.o: ../src/Tuple\ -\ Cat.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Tuple - Cat.d" -MT"src/Tuple\ -\ Cat.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



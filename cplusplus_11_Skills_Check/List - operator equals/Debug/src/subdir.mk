################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ operator\ equals.cpp 

OBJS += \
./src/List\ -\ operator\ equals.o 

CPP_DEPS += \
./src/List\ -\ operator\ equals.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ operator\ equals.o: ../src/List\ -\ operator\ equals.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - operator equals.d" -MT"src/List\ -\ operator\ equals.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



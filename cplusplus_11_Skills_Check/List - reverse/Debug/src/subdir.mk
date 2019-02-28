################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ reverse.cpp 

OBJS += \
./src/List\ -\ reverse.o 

CPP_DEPS += \
./src/List\ -\ reverse.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ reverse.o: ../src/List\ -\ reverse.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - reverse.d" -MT"src/List\ -\ reverse.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ swap.cpp 

OBJS += \
./src/List\ -\ swap.o 

CPP_DEPS += \
./src/List\ -\ swap.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ swap.o: ../src/List\ -\ swap.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - swap.d" -MT"src/List\ -\ swap.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



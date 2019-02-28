################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Stack\ -\ swap.cpp 

OBJS += \
./src/Stack\ -\ swap.o 

CPP_DEPS += \
./src/Stack\ -\ swap.d 


# Each subdirectory must supply rules for building sources it contributes
src/Stack\ -\ swap.o: ../src/Stack\ -\ swap.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Stack - swap.d" -MT"src/Stack\ -\ swap.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



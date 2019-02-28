################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Array\ -\ swap.cpp 

OBJS += \
./src/Array\ -\ swap.o 

CPP_DEPS += \
./src/Array\ -\ swap.d 


# Each subdirectory must supply rules for building sources it contributes
src/Array\ -\ swap.o: ../src/Array\ -\ swap.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Array - swap.d" -MT"src/Array\ -\ swap.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



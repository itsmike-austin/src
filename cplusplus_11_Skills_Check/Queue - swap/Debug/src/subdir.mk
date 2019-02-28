################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Queue\ -\ swap.cpp 

OBJS += \
./src/Queue\ -\ swap.o 

CPP_DEPS += \
./src/Queue\ -\ swap.d 


# Each subdirectory must supply rules for building sources it contributes
src/Queue\ -\ swap.o: ../src/Queue\ -\ swap.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Queue - swap.d" -MT"src/Queue\ -\ swap.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



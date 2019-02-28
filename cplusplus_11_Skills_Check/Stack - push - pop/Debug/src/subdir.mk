################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Stack\ -\ push\ -\ pop.cpp 

OBJS += \
./src/Stack\ -\ push\ -\ pop.o 

CPP_DEPS += \
./src/Stack\ -\ push\ -\ pop.d 


# Each subdirectory must supply rules for building sources it contributes
src/Stack\ -\ push\ -\ pop.o: ../src/Stack\ -\ push\ -\ pop.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Stack - push - pop.d" -MT"src/Stack\ -\ push\ -\ pop.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



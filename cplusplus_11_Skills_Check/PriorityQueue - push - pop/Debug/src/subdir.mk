################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Queue\ -\ push\ -\ pop.cpp 

OBJS += \
./src/Queue\ -\ push\ -\ pop.o 

CPP_DEPS += \
./src/Queue\ -\ push\ -\ pop.d 


# Each subdirectory must supply rules for building sources it contributes
src/Queue\ -\ push\ -\ pop.o: ../src/Queue\ -\ push\ -\ pop.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Queue - push - pop.d" -MT"src/Queue\ -\ push\ -\ pop.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



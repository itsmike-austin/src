################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Valarray\ -\ sum\ of\ elements.cpp 

OBJS += \
./src/Valarray\ -\ sum\ of\ elements.o 

CPP_DEPS += \
./src/Valarray\ -\ sum\ of\ elements.d 


# Each subdirectory must supply rules for building sources it contributes
src/Valarray\ -\ sum\ of\ elements.o: ../src/Valarray\ -\ sum\ of\ elements.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Valarray - sum of elements.d" -MT"src/Valarray\ -\ sum\ of\ elements.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


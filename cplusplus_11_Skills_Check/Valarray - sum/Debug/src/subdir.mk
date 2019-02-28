################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Valarray\ -\ sum.cpp 

OBJS += \
./src/Valarray\ -\ sum.o 

CPP_DEPS += \
./src/Valarray\ -\ sum.d 


# Each subdirectory must supply rules for building sources it contributes
src/Valarray\ -\ sum.o: ../src/Valarray\ -\ sum.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Valarray - sum.d" -MT"src/Valarray\ -\ sum.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



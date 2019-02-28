################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Valarray\ -\ resize.cpp 

OBJS += \
./src/Valarray\ -\ resize.o 

CPP_DEPS += \
./src/Valarray\ -\ resize.d 


# Each subdirectory must supply rules for building sources it contributes
src/Valarray\ -\ resize.o: ../src/Valarray\ -\ resize.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Valarray - resize.d" -MT"src/Valarray\ -\ resize.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



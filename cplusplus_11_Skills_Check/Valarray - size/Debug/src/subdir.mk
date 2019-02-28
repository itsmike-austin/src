################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Valarray\ -\ size.cpp 

OBJS += \
./src/Valarray\ -\ size.o 

CPP_DEPS += \
./src/Valarray\ -\ size.d 


# Each subdirectory must supply rules for building sources it contributes
src/Valarray\ -\ size.o: ../src/Valarray\ -\ size.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Valarray - size.d" -MT"src/Valarray\ -\ size.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



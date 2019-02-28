################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Valarray\ -\ Constructor.cpp 

OBJS += \
./src/Valarray\ -\ Constructor.o 

CPP_DEPS += \
./src/Valarray\ -\ Constructor.d 


# Each subdirectory must supply rules for building sources it contributes
src/Valarray\ -\ Constructor.o: ../src/Valarray\ -\ Constructor.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++98 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Valarray - Constructor.d" -MT"src/Valarray\ -\ Constructor.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



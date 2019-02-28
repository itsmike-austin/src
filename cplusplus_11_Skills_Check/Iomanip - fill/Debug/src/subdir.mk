################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Iomanip\ -\ fill.cpp 

OBJS += \
./src/Iomanip\ -\ fill.o 

CPP_DEPS += \
./src/Iomanip\ -\ fill.d 


# Each subdirectory must supply rules for building sources it contributes
src/Iomanip\ -\ fill.o: ../src/Iomanip\ -\ fill.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Iomanip - fill.d" -MT"src/Iomanip\ -\ fill.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



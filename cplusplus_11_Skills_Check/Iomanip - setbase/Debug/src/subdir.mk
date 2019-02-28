################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Iomanip\ -\ setbase.cpp 

OBJS += \
./src/Iomanip\ -\ setbase.o 

CPP_DEPS += \
./src/Iomanip\ -\ setbase.d 


# Each subdirectory must supply rules for building sources it contributes
src/Iomanip\ -\ setbase.o: ../src/Iomanip\ -\ setbase.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Iomanip - setbase.d" -MT"src/Iomanip\ -\ setbase.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



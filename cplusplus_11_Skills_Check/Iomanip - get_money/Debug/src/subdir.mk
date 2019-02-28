################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Iomanip\ -\ get_money.cpp 

OBJS += \
./src/Iomanip\ -\ get_money.o 

CPP_DEPS += \
./src/Iomanip\ -\ get_money.d 


# Each subdirectory must supply rules for building sources it contributes
src/Iomanip\ -\ get_money.o: ../src/Iomanip\ -\ get_money.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Iomanip - get_money.d" -MT"src/Iomanip\ -\ get_money.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



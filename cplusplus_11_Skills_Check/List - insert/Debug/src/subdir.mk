################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ insert.cpp 

OBJS += \
./src/List\ -\ insert.o 

CPP_DEPS += \
./src/List\ -\ insert.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ insert.o: ../src/List\ -\ insert.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - insert.d" -MT"src/List\ -\ insert.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



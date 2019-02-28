################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ assign.cpp 

OBJS += \
./src/List\ -\ assign.o 

CPP_DEPS += \
./src/List\ -\ assign.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ assign.o: ../src/List\ -\ assign.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - assign.d" -MT"src/List\ -\ assign.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



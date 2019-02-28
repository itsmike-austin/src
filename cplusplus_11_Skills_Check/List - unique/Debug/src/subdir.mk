################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ unique.cpp 

OBJS += \
./src/List\ -\ unique.o 

CPP_DEPS += \
./src/List\ -\ unique.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ unique.o: ../src/List\ -\ unique.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - unique.d" -MT"src/List\ -\ unique.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



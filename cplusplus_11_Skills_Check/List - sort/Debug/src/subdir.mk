################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ sort.cpp 

OBJS += \
./src/List\ -\ sort.o 

CPP_DEPS += \
./src/List\ -\ sort.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ sort.o: ../src/List\ -\ sort.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - sort.d" -MT"src/List\ -\ sort.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



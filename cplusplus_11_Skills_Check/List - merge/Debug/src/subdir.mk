################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ merge.cpp 

OBJS += \
./src/List\ -\ merge.o 

CPP_DEPS += \
./src/List\ -\ merge.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ merge.o: ../src/List\ -\ merge.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - merge.d" -MT"src/List\ -\ merge.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



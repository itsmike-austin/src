################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Iterator\ -\ iterator.cpp 

OBJS += \
./src/Iterator\ -\ iterator.o 

CPP_DEPS += \
./src/Iterator\ -\ iterator.d 


# Each subdirectory must supply rules for building sources it contributes
src/Iterator\ -\ iterator.o: ../src/Iterator\ -\ iterator.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Iterator - iterator.d" -MT"src/Iterator\ -\ iterator.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



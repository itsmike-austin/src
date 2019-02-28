################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ equal.cpp 

OBJS += \
./src/Algorithm\ -\ equal.o 

CPP_DEPS += \
./src/Algorithm\ -\ equal.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ equal.o: ../src/Algorithm\ -\ equal.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - equal.d" -MT"src/Algorithm\ -\ equal.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



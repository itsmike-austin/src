################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ any_of.cpp 

OBJS += \
./src/Algorithm\ -\ any_of.o 

CPP_DEPS += \
./src/Algorithm\ -\ any_of.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ any_of.o: ../src/Algorithm\ -\ any_of.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - any_of.d" -MT"src/Algorithm\ -\ any_of.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



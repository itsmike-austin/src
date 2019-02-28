################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ count.cpp 

OBJS += \
./src/Algorithm\ -\ count.o 

CPP_DEPS += \
./src/Algorithm\ -\ count.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ count.o: ../src/Algorithm\ -\ count.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - count.d" -MT"src/Algorithm\ -\ count.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



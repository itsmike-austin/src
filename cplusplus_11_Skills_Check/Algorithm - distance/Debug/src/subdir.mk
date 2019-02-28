################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ distance.cpp 

OBJS += \
./src/Algorithm\ -\ distance.o 

CPP_DEPS += \
./src/Algorithm\ -\ distance.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ distance.o: ../src/Algorithm\ -\ distance.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - distance.d" -MT"src/Algorithm\ -\ distance.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



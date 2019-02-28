################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ find_if.cpp 

OBJS += \
./src/Algorithm\ -\ find_if.o 

CPP_DEPS += \
./src/Algorithm\ -\ find_if.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ find_if.o: ../src/Algorithm\ -\ find_if.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - find_if.d" -MT"src/Algorithm\ -\ find_if.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



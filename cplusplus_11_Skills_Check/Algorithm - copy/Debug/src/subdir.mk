################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ copy.cpp 

OBJS += \
./src/Algorithm\ -\ copy.o 

CPP_DEPS += \
./src/Algorithm\ -\ copy.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ copy.o: ../src/Algorithm\ -\ copy.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - copy.d" -MT"src/Algorithm\ -\ copy.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



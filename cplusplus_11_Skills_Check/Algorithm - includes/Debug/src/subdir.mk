################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ includes.cpp 

OBJS += \
./src/Algorithm\ -\ includes.o 

CPP_DEPS += \
./src/Algorithm\ -\ includes.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ includes.o: ../src/Algorithm\ -\ includes.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - includes.d" -MT"src/Algorithm\ -\ includes.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



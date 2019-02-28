################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ generate.cpp 

OBJS += \
./src/Algorithm\ -\ generate.o 

CPP_DEPS += \
./src/Algorithm\ -\ generate.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ generate.o: ../src/Algorithm\ -\ generate.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - generate.d" -MT"src/Algorithm\ -\ generate.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



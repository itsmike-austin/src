################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ for_each.cpp 

OBJS += \
./src/Algorithm\ -\ for_each.o 

CPP_DEPS += \
./src/Algorithm\ -\ for_each.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ for_each.o: ../src/Algorithm\ -\ for_each.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - for_each.d" -MT"src/Algorithm\ -\ for_each.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



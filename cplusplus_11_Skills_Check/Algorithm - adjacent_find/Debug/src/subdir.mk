################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ adjacent_find.cpp 

OBJS += \
./src/Algorithm\ -\ adjacent_find.o 

CPP_DEPS += \
./src/Algorithm\ -\ adjacent_find.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ adjacent_find.o: ../src/Algorithm\ -\ adjacent_find.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - adjacent_find.d" -MT"src/Algorithm\ -\ adjacent_find.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



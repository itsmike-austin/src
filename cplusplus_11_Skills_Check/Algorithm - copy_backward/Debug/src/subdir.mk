################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ copy_backward.cpp 

OBJS += \
./src/Algorithm\ -\ copy_backward.o 

CPP_DEPS += \
./src/Algorithm\ -\ copy_backward.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ copy_backward.o: ../src/Algorithm\ -\ copy_backward.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - copy_backward.d" -MT"src/Algorithm\ -\ copy_backward.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



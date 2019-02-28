################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ iter_swap.cpp 

OBJS += \
./src/Algorithm\ -\ iter_swap.o 

CPP_DEPS += \
./src/Algorithm\ -\ iter_swap.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ iter_swap.o: ../src/Algorithm\ -\ iter_swap.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - iter_swap.d" -MT"src/Algorithm\ -\ iter_swap.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



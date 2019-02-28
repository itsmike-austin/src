################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ copy_n.cpp 

OBJS += \
./src/Algorithm\ -\ copy_n.o 

CPP_DEPS += \
./src/Algorithm\ -\ copy_n.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ copy_n.o: ../src/Algorithm\ -\ copy_n.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - copy_n.d" -MT"src/Algorithm\ -\ copy_n.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ lexicographical_compare.cpp 

OBJS += \
./src/Algorithm\ -\ lexicographical_compare.o 

CPP_DEPS += \
./src/Algorithm\ -\ lexicographical_compare.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ lexicographical_compare.o: ../src/Algorithm\ -\ lexicographical_compare.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - lexicographical_compare.d" -MT"src/Algorithm\ -\ lexicographical_compare.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ binary_search.cpp 

OBJS += \
./src/Algorithm\ -\ binary_search.o 

CPP_DEPS += \
./src/Algorithm\ -\ binary_search.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ binary_search.o: ../src/Algorithm\ -\ binary_search.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - binary_search.d" -MT"src/Algorithm\ -\ binary_search.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



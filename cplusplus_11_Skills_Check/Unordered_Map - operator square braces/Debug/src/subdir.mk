################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Unordered_Map\ -\ operator\ square\ braces.cpp 

OBJS += \
./src/Unordered_Map\ -\ operator\ square\ braces.o 

CPP_DEPS += \
./src/Unordered_Map\ -\ operator\ square\ braces.d 


# Each subdirectory must supply rules for building sources it contributes
src/Unordered_Map\ -\ operator\ square\ braces.o: ../src/Unordered_Map\ -\ operator\ square\ braces.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Unordered_Map - operator square braces.d" -MT"src/Unordered_Map\ -\ operator\ square\ braces.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



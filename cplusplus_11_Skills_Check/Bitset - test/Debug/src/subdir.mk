################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Bitset\ -\ test.cpp 

OBJS += \
./src/Bitset\ -\ test.o 

CPP_DEPS += \
./src/Bitset\ -\ test.d 


# Each subdirectory must supply rules for building sources it contributes
src/Bitset\ -\ test.o: ../src/Bitset\ -\ test.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Bitset - test.d" -MT"src/Bitset\ -\ test.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



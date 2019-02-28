################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Bitset\ -\ none\ -\ array\ test.cpp 

OBJS += \
./src/Bitset\ -\ none\ -\ array\ test.o 

CPP_DEPS += \
./src/Bitset\ -\ none\ -\ array\ test.d 


# Each subdirectory must supply rules for building sources it contributes
src/Bitset\ -\ none\ -\ array\ test.o: ../src/Bitset\ -\ none\ -\ array\ test.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Bitset - none - array test.d" -MT"src/Bitset\ -\ none\ -\ array\ test.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



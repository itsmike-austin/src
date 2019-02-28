################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Bitset\ -\ reset.cpp 

OBJS += \
./src/Bitset\ -\ reset.o 

CPP_DEPS += \
./src/Bitset\ -\ reset.d 


# Each subdirectory must supply rules for building sources it contributes
src/Bitset\ -\ reset.o: ../src/Bitset\ -\ reset.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Bitset - reset.d" -MT"src/Bitset\ -\ reset.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Bitset\ -\ all.cpp 

OBJS += \
./src/Bitset\ -\ all.o 

CPP_DEPS += \
./src/Bitset\ -\ all.d 


# Each subdirectory must supply rules for building sources it contributes
src/Bitset\ -\ all.o: ../src/Bitset\ -\ all.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Bitset - all.d" -MT"src/Bitset\ -\ all.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



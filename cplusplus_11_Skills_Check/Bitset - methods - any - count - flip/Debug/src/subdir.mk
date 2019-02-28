################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Bitset\ -\ methods\ -\ any\ -\ count\ -\ flip.cpp 

OBJS += \
./src/Bitset\ -\ methods\ -\ any\ -\ count\ -\ flip.o 

CPP_DEPS += \
./src/Bitset\ -\ methods\ -\ any\ -\ count\ -\ flip.d 


# Each subdirectory must supply rules for building sources it contributes
src/Bitset\ -\ methods\ -\ any\ -\ count\ -\ flip.o: ../src/Bitset\ -\ methods\ -\ any\ -\ count\ -\ flip.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Bitset - methods - any - count - flip.d" -MT"src/Bitset\ -\ methods\ -\ any\ -\ count\ -\ flip.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



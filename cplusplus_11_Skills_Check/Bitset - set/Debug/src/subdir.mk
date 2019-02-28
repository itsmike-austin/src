################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Bitset\ -\ set.cpp 

OBJS += \
./src/Bitset\ -\ set.o 

CPP_DEPS += \
./src/Bitset\ -\ set.d 


# Each subdirectory must supply rules for building sources it contributes
src/Bitset\ -\ set.o: ../src/Bitset\ -\ set.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Bitset - set.d" -MT"src/Bitset\ -\ set.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



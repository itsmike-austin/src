################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Bitset\ -\ to_string\ -\ to_ullong\ -\ to_ulong.cpp 

OBJS += \
./src/Bitset\ -\ to_string\ -\ to_ullong\ -\ to_ulong.o 

CPP_DEPS += \
./src/Bitset\ -\ to_string\ -\ to_ullong\ -\ to_ulong.d 


# Each subdirectory must supply rules for building sources it contributes
src/Bitset\ -\ to_string\ -\ to_ullong\ -\ to_ulong.o: ../src/Bitset\ -\ to_string\ -\ to_ullong\ -\ to_ulong.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Bitset - to_string - to_ullong - to_ulong.d" -MT"src/Bitset\ -\ to_string\ -\ to_ullong\ -\ to_ulong.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



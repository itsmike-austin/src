################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Fstream\ -\ rdbuf.cpp 

OBJS += \
./src/Fstream\ -\ rdbuf.o 

CPP_DEPS += \
./src/Fstream\ -\ rdbuf.d 


# Each subdirectory must supply rules for building sources it contributes
src/Fstream\ -\ rdbuf.o: ../src/Fstream\ -\ rdbuf.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Fstream - rdbuf.d" -MT"src/Fstream\ -\ rdbuf.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ operator\ square\ brace.cpp 

OBJS += \
./src/Vector\ -\ operator\ square\ brace.o 

CPP_DEPS += \
./src/Vector\ -\ operator\ square\ brace.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ operator\ square\ brace.o: ../src/Vector\ -\ operator\ square\ brace.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - operator square brace.d" -MT"src/Vector\ -\ operator\ square\ brace.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ rbegin\ -\ rend.cpp 

OBJS += \
./src/Vector\ -\ rbegin\ -\ rend.o 

CPP_DEPS += \
./src/Vector\ -\ rbegin\ -\ rend.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ rbegin\ -\ rend.o: ../src/Vector\ -\ rbegin\ -\ rend.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - rbegin - rend.d" -MT"src/Vector\ -\ rbegin\ -\ rend.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



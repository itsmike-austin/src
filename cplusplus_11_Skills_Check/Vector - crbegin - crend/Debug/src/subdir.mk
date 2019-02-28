################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ crbegin\ -\ crend.cpp 

OBJS += \
./src/Vector\ -\ crbegin\ -\ crend.o 

CPP_DEPS += \
./src/Vector\ -\ crbegin\ -\ crend.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ crbegin\ -\ crend.o: ../src/Vector\ -\ crbegin\ -\ crend.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - crbegin - crend.d" -MT"src/Vector\ -\ crbegin\ -\ crend.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



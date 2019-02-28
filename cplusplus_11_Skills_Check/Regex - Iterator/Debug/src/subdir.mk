################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Regex\ -\ Iterator.cpp 

OBJS += \
./src/Regex\ -\ Iterator.o 

CPP_DEPS += \
./src/Regex\ -\ Iterator.d 


# Each subdirectory must supply rules for building sources it contributes
src/Regex\ -\ Iterator.o: ../src/Regex\ -\ Iterator.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Regex - Iterator.d" -MT"src/Regex\ -\ Iterator.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



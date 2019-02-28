################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Regex\ -\ Token\ Iterator.cpp 

OBJS += \
./src/Regex\ -\ Token\ Iterator.o 

CPP_DEPS += \
./src/Regex\ -\ Token\ Iterator.d 


# Each subdirectory must supply rules for building sources it contributes
src/Regex\ -\ Token\ Iterator.o: ../src/Regex\ -\ Token\ Iterator.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Regex - Token Iterator.d" -MT"src/Regex\ -\ Token\ Iterator.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



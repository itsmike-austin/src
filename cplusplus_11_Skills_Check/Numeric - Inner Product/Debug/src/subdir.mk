################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Numeric\ -\ Inner\ Product.cpp 

OBJS += \
./src/Numeric\ -\ Inner\ Product.o 

CPP_DEPS += \
./src/Numeric\ -\ Inner\ Product.d 


# Each subdirectory must supply rules for building sources it contributes
src/Numeric\ -\ Inner\ Product.o: ../src/Numeric\ -\ Inner\ Product.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Numeric - Inner Product.d" -MT"src/Numeric\ -\ Inner\ Product.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ emplace\ -\ emplace_back\ -\ emplace-front.cpp 

OBJS += \
./src/List\ -\ emplace\ -\ emplace_back\ -\ emplace-front.o 

CPP_DEPS += \
./src/List\ -\ emplace\ -\ emplace_back\ -\ emplace-front.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ emplace\ -\ emplace_back\ -\ emplace-front.o: ../src/List\ -\ emplace\ -\ emplace_back\ -\ emplace-front.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - emplace - emplace_back - emplace-front.d" -MT"src/List\ -\ emplace\ -\ emplace_back\ -\ emplace-front.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



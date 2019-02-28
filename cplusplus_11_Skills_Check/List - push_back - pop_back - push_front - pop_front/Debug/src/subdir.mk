################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ push_back\ -\ pop_back\ -\ push_front\ -\ pop_front.cpp 

OBJS += \
./src/List\ -\ push_back\ -\ pop_back\ -\ push_front\ -\ pop_front.o 

CPP_DEPS += \
./src/List\ -\ push_back\ -\ pop_back\ -\ push_front\ -\ pop_front.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ push_back\ -\ pop_back\ -\ push_front\ -\ pop_front.o: ../src/List\ -\ push_back\ -\ pop_back\ -\ push_front\ -\ pop_front.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - push_back - pop_back - push_front - pop_front.d" -MT"src/List\ -\ push_back\ -\ pop_back\ -\ push_front\ -\ pop_front.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



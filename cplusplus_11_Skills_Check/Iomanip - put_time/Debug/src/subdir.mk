################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Iomanip\ -\ put_time.cpp 

OBJS += \
./src/Iomanip\ -\ put_time.o 

CPP_DEPS += \
./src/Iomanip\ -\ put_time.d 


# Each subdirectory must supply rules for building sources it contributes
src/Iomanip\ -\ put_time.o: ../src/Iomanip\ -\ put_time.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Iomanip - put_time.d" -MT"src/Iomanip\ -\ put_time.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



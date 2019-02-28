################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Iomanip\ -\ setw.cpp 

OBJS += \
./src/Iomanip\ -\ setw.o 

CPP_DEPS += \
./src/Iomanip\ -\ setw.d 


# Each subdirectory must supply rules for building sources it contributes
src/Iomanip\ -\ setw.o: ../src/Iomanip\ -\ setw.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Iomanip - setw.d" -MT"src/Iomanip\ -\ setw.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Iomanip\ -\ setprecision.cpp 

OBJS += \
./src/Iomanip\ -\ setprecision.o 

CPP_DEPS += \
./src/Iomanip\ -\ setprecision.d 


# Each subdirectory must supply rules for building sources it contributes
src/Iomanip\ -\ setprecision.o: ../src/Iomanip\ -\ setprecision.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Iomanip - setprecision.d" -MT"src/Iomanip\ -\ setprecision.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



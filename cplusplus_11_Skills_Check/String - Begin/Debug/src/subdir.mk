################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/String\ -\ Begin.cpp 

OBJS += \
./src/String\ -\ Begin.o 

CPP_DEPS += \
./src/String\ -\ Begin.d 


# Each subdirectory must supply rules for building sources it contributes
src/String\ -\ Begin.o: ../src/String\ -\ Begin.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/String - Begin.d" -MT"src/String\ -\ Begin.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



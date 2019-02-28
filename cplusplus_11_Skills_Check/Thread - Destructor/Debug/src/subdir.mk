################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Thread\ -\ Destructor.cpp 

OBJS += \
./src/Thread\ -\ Destructor.o 

CPP_DEPS += \
./src/Thread\ -\ Destructor.d 


# Each subdirectory must supply rules for building sources it contributes
src/Thread\ -\ Destructor.o: ../src/Thread\ -\ Destructor.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Thread - Destructor.d" -MT"src/Thread\ -\ Destructor.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



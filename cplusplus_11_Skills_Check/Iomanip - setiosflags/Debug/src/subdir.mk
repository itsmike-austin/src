################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Iomanip\ -\ setiosflags.cpp 

OBJS += \
./src/Iomanip\ -\ setiosflags.o 

CPP_DEPS += \
./src/Iomanip\ -\ setiosflags.d 


# Each subdirectory must supply rules for building sources it contributes
src/Iomanip\ -\ setiosflags.o: ../src/Iomanip\ -\ setiosflags.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Iomanip - setiosflags.d" -MT"src/Iomanip\ -\ setiosflags.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



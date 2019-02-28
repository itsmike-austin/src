################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Iomanip\ -\ resetiosflags.cpp 

OBJS += \
./src/Iomanip\ -\ resetiosflags.o 

CPP_DEPS += \
./src/Iomanip\ -\ resetiosflags.d 


# Each subdirectory must supply rules for building sources it contributes
src/Iomanip\ -\ resetiosflags.o: ../src/Iomanip\ -\ resetiosflags.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Iomanip - resetiosflags.d" -MT"src/Iomanip\ -\ resetiosflags.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Regex\ -\ Replace.cpp 

OBJS += \
./src/Regex\ -\ Replace.o 

CPP_DEPS += \
./src/Regex\ -\ Replace.d 


# Each subdirectory must supply rules for building sources it contributes
src/Regex\ -\ Replace.o: ../src/Regex\ -\ Replace.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Regex - Replace.d" -MT"src/Regex\ -\ Replace.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ empty\ --\ test\ if\ list\ is\ empty.cpp 

OBJS += \
./src/List\ -\ empty\ --\ test\ if\ list\ is\ empty.o 

CPP_DEPS += \
./src/List\ -\ empty\ --\ test\ if\ list\ is\ empty.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ empty\ --\ test\ if\ list\ is\ empty.o: ../src/List\ -\ empty\ --\ test\ if\ list\ is\ empty.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - empty -- test if list is empty.d" -MT"src/List\ -\ empty\ --\ test\ if\ list\ is\ empty.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



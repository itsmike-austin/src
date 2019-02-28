################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Ios\ -\ ios_base\ -\ fmtflags.cpp 

OBJS += \
./src/Ios\ -\ ios_base\ -\ fmtflags.o 

CPP_DEPS += \
./src/Ios\ -\ ios_base\ -\ fmtflags.d 


# Each subdirectory must supply rules for building sources it contributes
src/Ios\ -\ ios_base\ -\ fmtflags.o: ../src/Ios\ -\ ios_base\ -\ fmtflags.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Ios - ios_base - fmtflags.d" -MT"src/Ios\ -\ ios_base\ -\ fmtflags.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



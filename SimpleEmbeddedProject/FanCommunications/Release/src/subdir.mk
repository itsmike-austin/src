################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DGramSocket.c \
../src/FanCommunications.c \
../src/OutputError.c \
../src/Semaphore.c \
../src/SharedMemory.c 

OBJS += \
./src/DGramSocket.o \
./src/FanCommunications.o \
./src/OutputError.o \
./src/Semaphore.o \
./src/SharedMemory.o 

C_DEPS += \
./src/DGramSocket.d \
./src/FanCommunications.d \
./src/OutputError.d \
./src/Semaphore.d \
./src/SharedMemory.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



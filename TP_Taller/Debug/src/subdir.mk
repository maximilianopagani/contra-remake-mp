################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Bullet.cpp \
../src/ContraRemake.cpp \
../src/Game.cpp \
../src/Grapher.cpp \
../src/Personaje.cpp 

OBJS += \
./src/Bullet.o \
./src/ContraRemake.o \
./src/Game.o \
./src/Grapher.o \
./src/Personaje.o 

CPP_DEPS += \
./src/Bullet.d \
./src/ContraRemake.d \
./src/Game.d \
./src/Grapher.d \
./src/Personaje.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



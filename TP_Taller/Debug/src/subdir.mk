################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Bullet.cpp \
../src/ContraRemake.cpp \
../src/Game.cpp \
../src/Grapher.cpp \
../src/Level.cpp \
../src/Logger.cpp \
../src/Personaje.cpp \
../src/Utils.cpp \
../src/testLogger.cpp 

OBJS += \
./src/Bullet.o \
./src/ContraRemake.o \
./src/Game.o \
./src/Grapher.o \
./src/Level.o \
./src/Logger.o \
./src/Personaje.o \
./src/Utils.o \
./src/testLogger.o 

CPP_DEPS += \
./src/Bullet.d \
./src/ContraRemake.d \
./src/Game.d \
./src/Grapher.d \
./src/Level.d \
./src/Logger.d \
./src/Personaje.d \
./src/Utils.d \
./src/testLogger.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



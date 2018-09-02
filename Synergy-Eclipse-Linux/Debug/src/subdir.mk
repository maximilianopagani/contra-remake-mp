################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Juego.cpp \
../src/Personaje.cpp \
../src/TP-Taller.cpp \
../src/TexturaGenerador.cpp 

OBJS += \
./src/Juego.o \
./src/Personaje.o \
./src/TP-Taller.o \
./src/TexturaGenerador.o 

CPP_DEPS += \
./src/Juego.d \
./src/Personaje.d \
./src/TP-Taller.d \
./src/TexturaGenerador.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



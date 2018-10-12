################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Utils/CollisionHelper.cpp \
../src/Utils/Constants.cpp \
../src/Utils/Logger.cpp \
../src/Utils/PlatformParser.cpp \
../src/Utils/PlayerStateHandler.cpp \
../src/Utils/Utils.cpp 

OBJS += \
./src/Utils/CollisionHelper.o \
./src/Utils/Constants.o \
./src/Utils/Logger.o \
./src/Utils/PlatformParser.o \
./src/Utils/PlayerStateHandler.o \
./src/Utils/Utils.o 

CPP_DEPS += \
./src/Utils/CollisionHelper.d \
./src/Utils/Constants.d \
./src/Utils/Logger.d \
./src/Utils/PlatformParser.d \
./src/Utils/PlayerStateHandler.d \
./src/Utils/Utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/Utils/%.o: ../src/Utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



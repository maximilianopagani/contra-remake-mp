################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/data/tinyxml/tinystr.cpp \
../src/data/tinyxml/tinyxml.cpp \
../src/data/tinyxml/tinyxmlerror.cpp \
../src/data/tinyxml/tinyxmlparser.cpp 

OBJS += \
./src/data/tinyxml/tinystr.o \
./src/data/tinyxml/tinyxml.o \
./src/data/tinyxml/tinyxmlerror.o \
./src/data/tinyxml/tinyxmlparser.o 

CPP_DEPS += \
./src/data/tinyxml/tinystr.d \
./src/data/tinyxml/tinyxml.d \
./src/data/tinyxml/tinyxmlerror.d \
./src/data/tinyxml/tinyxmlparser.d 


# Each subdirectory must supply rules for building sources it contributes
src/data/tinyxml/%.o: ../src/data/tinyxml/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



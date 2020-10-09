################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../accels.c \
../annexe.c \
../asservissement.c \
../asserv_haut.c \
../centrale.c \
../interruptions_init.c \
../interruptions_routines.c \
../main.c \
../pid.c \
../sonar.c \
../timers_init.c \
../voltmetre.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
accels.o \
annexe.o \
asservissement.o \
asserv_haut.o \
centrale.o \
interruptions_init.o \
interruptions_routines.o \
main.o \
pid.o \
sonar.o \
timers_init.o \
voltmetre.o

OBJS_AS_ARGS +=  \
accels.o \
annexe.o \
asservissement.o \
asserv_haut.o \
centrale.o \
interruptions_init.o \
interruptions_routines.o \
main.o \
pid.o \
sonar.o \
timers_init.o \
voltmetre.o

C_DEPS +=  \
accels.d \
annexe.d \
asservissement.d \
asserv_haut.d \
centrale.d \
interruptions_init.d \
interruptions_routines.d \
main.d \
pid.d \
sonar.d \
timers_init.d \
voltmetre.d

C_DEPS_AS_ARGS +=  \
accels.d \
annexe.d \
asservissement.d \
asserv_haut.d \
centrale.d \
interruptions_init.d \
interruptions_routines.d \
main.d \
pid.d \
sonar.d \
timers_init.d \
voltmetre.d

OUTPUT_FILE_PATH +=projet_quadricoptere.elf

OUTPUT_FILE_PATH_AS_ARGS +=projet_quadricoptere.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler

























./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DF_CPU=16000000  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\include"  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -mmcu=atmega1280 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\gcc\dev\atmega1280" -c -gdwarf-2 -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="projet_quadricoptere.map" -Wl,--start-group  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega1280 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\gcc\dev\atmega1280"  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "projet_quadricoptere.elf" "projet_quadricoptere.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "projet_quadricoptere.elf" "projet_quadricoptere.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "projet_quadricoptere.elf" > "projet_quadricoptere.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "projet_quadricoptere.elf" "projet_quadricoptere.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "projet_quadricoptere.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "projet_quadricoptere.elf" "projet_quadricoptere.a" "projet_quadricoptere.hex" "projet_quadricoptere.lss" "projet_quadricoptere.eep" "projet_quadricoptere.map" "projet_quadricoptere.srec" "projet_quadricoptere.usersignatures"
	
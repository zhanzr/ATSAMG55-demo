
################################################################################
# Automatically-generated file. Do not edit!
################################################################################

ifdef SystemRoot
	SHELL = cmd.exe
	MK_DIR = mkdir
else
	ifeq ($(shell uname), Linux)
		MK_DIR = mkdir -p
	endif

	ifeq ($(shell uname | cut -d _ -f 1), CYGWIN)
		MK_DIR = mkdir -p
	endif

	ifeq ($(shell uname | cut -d _ -f 1), MINGW32)
		MK_DIR = mkdir -p
	endif

	ifeq ($(shell uname | cut -d _ -f 1), MINGW64)
		MK_DIR = mkdir -p
	endif
endif

# List the subdirectories for creating object files
SUB_DIRS +=  \
 \
hpl/mem2mem \
hpl/pmc \
hpl/usart \
hal/src \
hal/utils/src \
examples \
samg55/armcc \
hpl/core

# List the object files
OBJS +=  \
hal/src/hal_io.o \
samg55/armcc/system_samg55.o \
hpl/usart/hpl_usart.o \
hpl/pmc/hpl_pmc.o \
hal/src/hal_delay.o \
hpl/core/hpl_init.o \
edbg_uart_example.o \
hal/utils/src/utils_assert.o \
hpl/mem2mem/hpl_mem2mem.o \
atmel_start.o \
hpl/core/hpl_core_m4_base.o \
samg55/armcc/startup_samg55.o \
hal/src/hal_init.o \
hal/utils/src/utils_list.o \
examples/driver_examples.o \
driver_init.o \
hal/src/hal_usart_async.o \
hal/utils/src/utils_ringbuffer.o \
hal/src/hal_gpio.o \
hal/utils/src/utils_event.o \
hal/src/hal_sleep.o \
hpl/pmc/hpl_sleep.o \
hal/src/hal_atomic.o

OBJS_AS_ARGS +=  \
"hal/src/hal_io.o" \
"samg55/armcc/system_samg55.o" \
"hpl/usart/hpl_usart.o" \
"hpl/pmc/hpl_pmc.o" \
"hal/src/hal_delay.o" \
"hpl/core/hpl_init.o" \
"edbg_uart_example.o" \
"hal/utils/src/utils_assert.o" \
"hpl/mem2mem/hpl_mem2mem.o" \
"atmel_start.o" \
"hpl/core/hpl_core_m4_base.o" \
"samg55/armcc/startup_samg55.o" \
"hal/src/hal_init.o" \
"hal/utils/src/utils_list.o" \
"examples/driver_examples.o" \
"driver_init.o" \
"hal/src/hal_usart_async.o" \
"hal/utils/src/utils_ringbuffer.o" \
"hal/src/hal_gpio.o" \
"hal/utils/src/utils_event.o" \
"hal/src/hal_sleep.o" \
"hpl/pmc/hpl_sleep.o" \
"hal/src/hal_atomic.o"

# List the dependency files
DEPS := $(OBJS:%.o=%.d)

DEPS_AS_ARGS +=  \
"samg55/armcc/system_samg55.d" \
"hal/src/hal_gpio.d" \
"hal/src/hal_io.d" \
"hpl/usart/hpl_usart.d" \
"edbg_uart_example.d" \
"hpl/mem2mem/hpl_mem2mem.d" \
"hal/utils/src/utils_assert.d" \
"hal/src/hal_delay.d" \
"hpl/core/hpl_init.d" \
"samg55/armcc/startup_samg55.d" \
"hal/src/hal_init.d" \
"hpl/core/hpl_core_m4_base.d" \
"driver_init.d" \
"hpl/pmc/hpl_pmc.d" \
"hal/src/hal_usart_async.d" \
"examples/driver_examples.d" \
"hal/utils/src/utils_list.d" \
"hal/src/hal_sleep.d" \
"hal/utils/src/utils_ringbuffer.d" \
"hal/utils/src/utils_event.d" \
"atmel_start.d" \
"hal/src/hal_atomic.d" \
"hpl/pmc/hpl_sleep.d"

OUTPUT_FILE_NAME :=AtmelStart
QUOTE := "
OUTPUT_FILE_PATH +=$(OUTPUT_FILE_NAME).elf
OUTPUT_FILE_PATH_AS_ARGS +=$(OUTPUT_FILE_NAME).elf

vpath %.c ../
vpath %.s ../
vpath %.S ../

# All Target
all: $(SUB_DIRS) $(OUTPUT_FILE_PATH)

# Linker target

$(OUTPUT_FILE_PATH): $(OBJS)
	@echo Building target: $@
	@echo Invoking: ARMCC Linker
	$(QUOTE)armlink$(QUOTE) --ro-base 0x00000000 --entry 0x00000000 --rw-base 0x20000000 --entry Reset_Handler --first __Vectors \
--strict --summary_stderr --info summarysizes --map --xref --callgraph --symbols \
--info sizes --info totals --info unused --info veneers --list $(OUTPUT_FILE_NAME).map \
-o $(OUTPUT_FILE_NAME).elf --cpu Cortex-M4 \
$(OBJS_AS_ARGS)

	@echo Finished building target: $@

# Compiler target(s)




%.o: %.c
	@echo Building file: $<
	@echo ARMCC Compiler
	$(QUOTE)armcc$(QUOTE) --c99 -c -DDEBUG -O1 -g --apcs=interwork --split_sections --cpu Cortex-M4 -D__SAMG55J19__ \
-I"../" -I"../config" -I"../examples" -I"../hal/include" -I"../hal/utils/include" -I"../hpl/core" -I"../hpl/mem2mem" -I"../hpl/pio" -I"../hpl/pmc" -I"../hpl/usart" -I"../hri" -I"../" -I"../CMSIS/Core/Include" -I"../samg55/include"  \
--depend "$@"  -o "$@" "$<"

	@echo Finished building: $<

%.o: %.s
	@echo Building file: $<
	@echo ARMCC Assembler
	$(QUOTE)armasm$(QUOTE) -g --apcs=interwork --cpu Cortex-M4 --pd "D__SAMG55J19__ SETA 1" \
-I"../" -I"../config" -I"../examples" -I"../hal/include" -I"../hal/utils/include" -I"../hpl/core" -I"../hpl/mem2mem" -I"../hpl/pio" -I"../hpl/pmc" -I"../hpl/usart" -I"../hri" -I"../" -I"../CMSIS/Core/Include" -I"../samg55/include"  \
--depend "$(@:%.o=%.d)" -o "$@" "$<"

	@echo Finished building: $<

%.o: %.S
	@echo Building file: $<
	@echo ARMCC Preprocessing Assembler
	$(QUOTE)armcc$(QUOTE) --c99 -c -DDEBUG -O1 -g --apcs=interwork --split_sections --cpu Cortex-M4 -D__SAMG55J19__ \
-I"../" -I"../config" -I"../examples" -I"../hal/include" -I"../hal/utils/include" -I"../hpl/core" -I"../hpl/mem2mem" -I"../hpl/pio" -I"../hpl/pmc" -I"../hpl/usart" -I"../hri" -I"../" -I"../CMSIS/Core/Include" -I"../samg55/include"  \
--depend "$@"  -o "$@" "$<"

	@echo Finished building: $<

# Detect changes in the dependent files and recompile the respective object files.
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif
endif

$(SUB_DIRS):
	$(MK_DIR) "$@"

clean:
	rm -f $(OBJS_AS_ARGS)
	rm -f $(OUTPUT_FILE_PATH)
	rm -f $(DEPS_AS_ARGS)
	rm -f $(OUTPUT_FILE_NAME).map $(OUTPUT_FILE_NAME).elf

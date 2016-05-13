# Copyright (C) 2013, 2016 Enrico Rossi
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

PRG_NAME = tsunami_simulator
OPTLEV = s

## Microcontroller definition
#
MCU = atmega328p
FCPU = 16000000UL

PWD = $(shell pwd)
INC = -I/usr/lib/avr/include/

CFLAGS = $(INC) -Wall -Wstrict-prototypes -pedantic -mmcu=$(MCU) -O$(OPTLEV) -D F_CPU=$(FCPU)
LFLAGS = -lm

# Uncomment if git is in use
GIT_TAG = "$(shell git describe --tags --long --always)"
PRGNAME = $(PRG_NAME)_$(GIT_TAG)_$(MCU)
ELFNAME = $(PRGNAME)_$@

AR = avr-ar
CC = avr-gcc

# Arduino
DUDEAPORT = /dev/ttyACM0
DUDEADEV = arduino

# Stk500v2
DUDESPORT = /dev/ttyUSB0
DUDESDEV = stk500v2

# avrispmkII
DUDEUPORT = usb
DUDEUDEV = avrispmkII

# Use sudo for USB avrispmkII
DUDE = sudo avrdude -p $(MCU) -e -U flash:w:$(PRGNAME).hex

OBJCOPY = avr-objcopy -j .text -j .data -O ihex
OBJDUMP = avr-objdump
SIZE = avr-size --format=avr --mcu=$(MCU) $(PRGNAME).elf

REMOVE = rm -f

usart_obj = circular_buffer.o usart.o
usart_norfid_obj = circular_buffer.o usart_norfid.o

all_obj = $(usart_obj) rtc.o sonar.o

## expand CFLAGS
#
CFLAGS += -D USE_ARDUINO -D GITREL=\"$(GIT_TAG)\"

.PHONY: clean
.SILENT: help
.SUFFIXES: .c, .o

## Export variables used in sub-make
#
.EXPORT_ALL_VARIABLES: doc

## Default
#
all: $(all_obj)
	$(CC) $(CFLAGS) -o $(ELFNAME).elf main.c $(all_obj) $(LFLAGS)
	$(OBJCOPY) $(ELFNAME).elf $(PRGNAME).hex

program:
	$(DUDE) -c $(DUDEADEV) -P $(DUDEAPORT)

clean:
	$(REMOVE) *.elf *.hex $(all_obj)

version:
	# Last Git tag: $(GIT_TAG)

doc_timing:
	$(MAKE) -C ../doc timing

doc:
	$(MAKE) -C ../doc doc

size:
	$(SIZE)

#SHELL := /bin/bash
#PATH := /usr/local/bin:$(PATH)

pio = "~/.platformio/penv/bin/pio"

all:
	pio -f -c vim run

run:
	pio -f -c vim run --target upload

clean:
	pio -f -c vim run --target clean

program:
	pio -f -c vim run --target program

uploadfs:
	pio -f -c vim run --target uploadfs

update:
	pio -f -c vim update

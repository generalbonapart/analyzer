# Makefile for building embedded application.
# by Brian Fraser

# Edit this file to compile extra C files into their own programs.
SOURCES = test.c joystick.c utilities.c led.c digits.c sampler.c analysis.c MyApp.c
TARGET = app


PUBDIR = $(HOME)/cmpt433/public/myApps
# PUBDIR = .
OUTDIR = $(PUBDIR)

CROSS_TOOL = arm-linux-gnueabihf-
# CROSS_TOOL = 

CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow
# -pg for supporting gprof profiling.
# CFLAGS += -pg

all: app noworky

app: $(SOURCES)
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET) -lpthread -lm

noworky: noworky.c  
	$(CC_C) $(CFLAGS) noworky.c -o $(OUTDIR)/noworky

clean:
	rm -f $(OUTDIR)/$(TARGET)

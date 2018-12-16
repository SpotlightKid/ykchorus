#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = ykchorus

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	PluginYKChorus.cpp

FILES_UI  = \
	PluginArtworkYKChorus.cpp \
	PluginUIYKChorus.cpp

# --------------------------------------------------------------
# Do some magic

include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(HAVE_JACK),true)
TARGETS += jack
endif

TARGETS += dssi_dsp
TARGETS += ladspa
TARGETS += lv2_sep
TARGETS += vst

all: $(TARGETS)

# --------------------------------------------------------------

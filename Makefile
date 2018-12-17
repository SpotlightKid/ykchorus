#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

include dpf/Makefile.base.mk


PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin
LIBDIR ?= $(PREFIX)/lib
DSSI_DIR ?= $(LIBDIR)/dssi
LADSPA_DIR ?= $(LIBDIR)/ladspa
LV2_DIR ?= $(LIBDIR)/lv2
VST_DIR ?= $(LIBDIR)/vst


all: plugins gen

# --------------------------------------------------------------

dgl:
ifeq ($(HAVE_DGL),true)
	$(MAKE) -C dpf/dgl
endif

plugins: dgl
	$(MAKE) all -C plugins/YKChorus

ifneq ($(CROSS_COMPILING),true)
gen: plugins dpf/utils/lv2_ttl_generator
	@$(CURDIR)/dpf/utils/generate-ttl.sh
ifeq ($(MACOS),true)
	@$(CURDIR)/dpf/utils/generate-vst-bundles.sh
endif

dpf/utils/lv2_ttl_generator:
	$(MAKE) -C dpf/utils/lv2-ttl-generator
else
gen:
endif

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf/dgl
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator
	$(MAKE) clean -C plugins/YKChorus
	rm -rf bin build

install:
	@install -Dm755 bin/ykchorus-dssi$(LIB_EXT) -t $(DESTDIR)$(DSSI_DIR)
	@install -Dm755 bin/ykchorus-ladspa$(LIB_EXT) -t $(DESTDIR)$(LADSPA_DIR)
	@install -Dm755 bin/ykchorus-vst$(LIB_EXT) -t $(DESTDIR)$(VST_DIR)
	@install -dm755 $(DESTDIR)$(LV2_DIR) && \
		cp -rf bin/ykchorus.lv2 $(DESTDIR)$(LV2_DIR)
ifeq ($(HAVE_JACK),true)
	@install -Dm755 bin/ykchorus$(APP_EXT) -t $(DESTDIR)$(BINDIR)
endif

install-user:
	@install -Dm755 bin/ykchorus-dssi$(LIB_EXT) -t $(HOME)/.dssi
	@install -Dm755 bin/ykchorus-ladspa$(LIB_EXT) -t $(HOME)/.ladspa
	@install -Dm755 bin/ykchorus-vst$(LIB_EXT) -t $(HOME)/.vst
	@install -dm755 $(HOME)/.lv2 && \
		cp -rf bin/ykchorus.lv2 $(HOME)/.lv2
ifeq ($(HAVE_JACK),true)
	@install -Dm755 bin/ykchorus$(APP_EXT) -t $(HOME)/bin
endif

# --------------------------------------------------------------

.PHONY: plugins

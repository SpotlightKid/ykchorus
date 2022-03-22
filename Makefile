#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

include dpf/Makefile.base.mk


PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin
DESKTOPDIR ?= $(PREFIX)/share/applications
ICONDIR ?= $(PREFIX)/share/pixmaps
LIBDIR ?= $(PREFIX)/lib
DSSI_DIR ?= $(LIBDIR)/dssi
LADSPA_DIR ?= $(LIBDIR)/ladspa
LV2_DIR ?= $(LIBDIR)/lv2
VST_DIR ?= $(LIBDIR)/vst


all: plugins gen

# --------------------------------------------------------------

dgl:
ifeq ($(HAVE_DGL),true)
	$(MAKE) -C dpf/dgl ../build/libdgl-opengl.a
endif

plugins: dgl
	$(MAKE) -C plugins/YKChorus all

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

artwork:
	$(MAKE) -C plugins/YKChorus artwork

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf/dgl
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator
	$(MAKE) clean -C plugins/YKChorus
	rm -rf bin build

install: all
	@install -Dm755 bin/ykchorus-dssi$(LIB_EXT) -t $(DESTDIR)$(DSSI_DIR)
	@install -Dm755 bin/ykchorus-ladspa$(LIB_EXT) -t $(DESTDIR)$(LADSPA_DIR)
	@install -Dm755 bin/ykchorus-vst$(LIB_EXT) -t $(DESTDIR)$(VST_DIR)
	@install -dm755 $(DESTDIR)$(LV2_DIR) && \
		cp -rf bin/ykchorus.lv2 $(DESTDIR)$(LV2_DIR)
ifeq ($(HAVE_JACK),true)
	@install -Dm755 bin/ykchorus$(APP_EXT) -t $(DESTDIR)$(BINDIR)
ifeq ($(UNIX),true)
	@install -Dm644 resources/ykchorus.desktop -t $(DESTDIR)$(DESKTOPDIR)
	@install -Dm644 resources/ykchorus.png -t $(DESTDIR)$(ICONDIR)
endif
endif

install-user: all
	@install -Dm755 bin/ykchorus-dssi$(LIB_EXT) -t $(HOME)/.dssi
	@install -Dm755 bin/ykchorus-ladspa$(LIB_EXT) -t $(HOME)/.ladspa
	@install -Dm755 bin/ykchorus-vst$(LIB_EXT) -t $(HOME)/.vst
	@install -dm755 $(HOME)/.lv2 && \
		cp -rf bin/ykchorus.lv2 $(HOME)/.lv2
ifeq ($(HAVE_JACK),true)
	@install -Dm755 bin/ykchorus$(APP_EXT) -t $(HOME)/bin
ifeq ($(UNIX),true)
	@install -Dm644 resources/ykchorus.desktop -t $(HOME)/.local/share/applications
	@install -Dm644 resources/ykchorus.png -t $(HOME)/.local/share/pixmaps
endif
endif

# --------------------------------------------------------------

.PHONY: plugins

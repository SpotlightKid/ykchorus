#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

SKIP_NATIVE_AUDIO_FALLBACK ?= true

# error out if DPF is missing, unless the current rule is 'submodules'
define MISSING_SUBMODULES_ERROR
=============================================================================
DPF library not found in directory 'dpf'.
Please run "make submodules" to clone the missing Git submodules, then retry.
=============================================================================
endef

ifneq ($(MAKECMDGOALS), submodules)
ifeq (,$(wildcard dpf/Makefile.base.mk))
    $(info $(MISSING_SUBMODULES_ERROR))
    $(error Unable to continue)
else
    include dpf/Makefile.base.mk
endif
endif

# --------------------------------------------------------------
# Installation directories

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
LIBDIR ?= $(PREFIX)/lib
DESKTOPDIR ?= $(PREFIX)/share/applications
ICONDIR ?= $(PREFIX)/share/pixmaps
DSSI_DIR ?= $(LIBDIR)/dssi
LADSPA_DIR ?= $(LIBDIR)/ladspa
ifneq ($(MACOS_OR_WINDOWS),true)
LV2_DIR ?= $(LIBDIR)/lv2
VST2_DIR ?= $(LIBDIR)/vst
VST3_DIR ?= $(LIBDIR)/vst3
CLAP_DIR ?= $(LIBDIR)/clap
endif
ifeq ($(MACOS),true)
LV2_DIR ?= /Library/Audio/Plug-Ins/LV2
VST2_DIR ?= /Library/Audio/Plug-Ins/VST
VST3_DIR ?= /Library/Audio/Plug-Ins/VST3
CLAP_DIR ?= /Library/Audio/Plug-Ins/CLAP
endif
ifeq ($(WINDOWS),true)
LV2_DIR ?= $(COMMONPROGRAMFILES)/LV2
VST2_DIR ?= $(COMMONPROGRAMFILES)/VST2
VST3_DIR ?= $(COMMONPROGRAMFILES)/VST3
CLAP_DIR ?= $(COMMONPROGRAMFILES)/CLAP
endif

USER_DSSI_DIR ?= $(HOME)/.dssi
USER_LADSPA_DIR ?= $(HOME)/.ladspa
ifneq ($(MACOS_OR_WINDOWS),true)
USER_LV2_DIR ?= $(HOME)/.lv2
USER_VST2_DIR ?= $(HOME)/.vst
USER_VST3_DIR ?= $(HOME)/.vst3
USER_CLAP_DIR ?= $(HOME)/.clap
endif
ifeq ($(MACOS),true)
USER_LV2_DIR ?= $(HOME)/Library/Audio/Plug-Ins/LV2
USER_VST2_DIR ?= $(HOME)/Library/Audio/Plug-Ins/VST
USER_VST3_DIR ?= $(HOME)/Library/Audio/Plug-Ins/VST3
USER_CLAP_DIR ?= $(HOME)/Library/Audio/Plug-Ins/CLAP
endif
ifeq ($(WINDOWS),true)
USER_LV2_DIR ?= $(APPDATA)/LV2
USER_VST2_DIR ?= $(APPDATA)/VST
USER_VST3_DIR ?= $(APPDATA)/VST3
USER_CLAP_DIR ?= $(APPDATA)/CLAP
endif

export DESTDIR PREFIX BINDIR LIBDIR
export DSSI_DIR LADSPA_DIR LV2_DIR VST2_DIR VST3_DIR CLAP_DIR
export USER_DSSI_DIR USER_LADSPA_DIR USER_LV2_DIR USER_VST2_DIR USER_VST3_DIR USER_CLAP_DIR

PLUGINS = YKChorus

DPF_PATCHES = \
	patches/dpf/fix-lv2-version-export.patch

PLUGIN_BASE_URI = https://chrisarndt.de/plugins/

# --------------------------------------------------------------
# Targets

all: libs plugins gen

submodules:
	git submodule update --init --recursive

patch: $(DPF_PATCHES)
	@-for p in $(DPF_PATCHES); do \
		echo "Applying patch '$${p}'..."; \
		patch -d dpf -p1 -N -r - -i ../$${p}; \
	done

artwork:
	@for plug in $(PLUGINS); do \
		$(MAKE) -C plugins/$${plug} artwork; \
	done

libs: patch
	$(MAKE) -C dpf/dgl "../build/libdgl-opengl.a"

plugins: $(PLUGINS)

$(PLUGINS): artwork libs
	$(MAKE) all -C plugins/$@

ifneq ($(CROSS_COMPILING),true)
gen: plugins dpf/utils/lv2_ttl_generator
	@dpf/utils/generate-ttl.sh
ifeq ($(MACOS),true)
	@dpf/utils/generate-vst-bundles.sh
endif

dpf/utils/lv2_ttl_generator:
	$(MAKE) -C dpf/utils/lv2-ttl-generator
else
gen: plugins dpf/utils/lv2_ttl_generator.exe
	@dpf/utils/generate-ttl.sh

dpf/utils/lv2_ttl_generator.exe:
	$(MAKE) -C dpf/utils/lv2-ttl-generator WINDOWS=true
endif

# --------------------------------------------------------------

check: gen
	@echo "Please make sure you have the https://github.com/KXStudio/LV2-Extensions bundles"
	@echo "installed somewhere on your LV2_PATH."
	@for plug in $(PLUGINS); do \
		lv2lint -Mpack -q -s lv2_generate_ttl -t "Plugin Author Email" \
			-I bin/$${plug,,}.lv2/ "$(PLUGIN_BASE_URI)$${plug,,}"; \
	done

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf/dgl
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator
	@for plug in $(PLUGINS); do \
		$(MAKE) clean -C plugins/$${plug}; \
	done

install: all
	@for plug in $(PLUGINS); do \
		$(MAKE) install -C plugins/$${plug}; \
	done

install-user: all
	@for plug in $(PLUGINS); do \
		$(MAKE) install-user -C plugins/$${plug}; \
	done

# --------------------------------------------------------------

.PHONY: all clean gen install install-user libs lv2lint patch plugins submodule


# Changelog


## v0.2.4 (2024-04-26)

This release adds two more plugin formats. There are no changes to the plugin's
behaviour or output.

* Added building [CLAP] format plugin.
* Added building [VST3] format plugin.
* Updated DPF sub-module to commit 1504e7d3 on branch `main`.
* Updated readme.


## v0.2.3 (2022-03-22)

This is a maintenance release. There are no changes to the plugin's behaviour
or output.

* Added `.desktop` and icon for the JACK stand-alone program.
* Updated DPF sub-module to commit 86a621bf on branch `main`.
* Added patch for DPF to fix plugin version numbering.
* Changed plugin license field to SPDX URL.
* Updated code using deprecated DGL call signatures.
* Made readme updates, minor wording changes, spelling and markup fixes and
  corrections to description of compilation requirements.
* Build:
    * Fixed aarch64 build.
    * Added build scripts for win32/64 using MinGW.
    * Tweaked `dgl` make target do not build unneeded Cairo DGL variant.
    * Added `check` make target for lv2lint check of build plugin.
    * Added `submodules` make target to check out DPF submodule and abort with
      better error if DPF is missing.
    * Replaced `bundle-source.sh` with `create-git-archive.sh` script based on
      `git-archive-all`.


## v0.2.2 (2018-12-18)

* Tweaked GUI.


## v0.2.1 (2018-12-17)

* Fixed Makefile so that project actually compiles when freshly checked out /
  unpacked.


## v0.2.0 (2018-12-16)

* Added first attempt at a plug-in GUI.
* Added controls for chorus LFO rates.


## v0.1.0 (2018-12-14)

Initial release


[clap]: https://cleveraudio.org/
[vst3]: https://en.wikipedia.org/wiki/Virtual_Studio_Technology

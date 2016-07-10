**Please read [wiki](https://github.com/tommai78101/homebrew/wiki) to see past progress.**

# Homebrew

Testing homebrew stuffs.

This project uses Eclipse C/C++ for homebrew application development, and Citra 3DS emulator for homebrew debugging/testing.

### Purpose

Display working 3D cube model, with the flexible Console outputs still enabled. Core engine is now running perfectly fine.

### Results

Citra 3DS Qt result:

![](http://i.imgur.com/Ai8Uvxt.png)

### Known Issue

* Do not run with citra.exe (Non-Qt build).

![](http://i.imgur.com/fIGscMk.png)

### Building

Since the Makefile is a bit customized, here is a table for specific `make` commands:

|Make commands|Action|Requirements|
|---|---|---|
|make all|Generates 3DSX and SMDH files.|Requires following [this wiki guide](https://github.com/wedr2/Guide/wiki/Setting-up-3DS-Homebrew-development-environment-using-Eclipse-CDT-for-C-and-CPP).|
|make cia|Generates 3DSX, CIA, and SMDH files.|Requires `makerom`|
|make sideload|Generates 3DSX file, then netloads to your Nintendo 3DS device.|Requires Homebrew Launcher v1.1.0|
|make citra|Generates 3DSX file, then launches the application via Citra emulator.|Requires Citra 3DS emulator. Make sure to change filepath in Makefile.|


# Homebrew

Testing homebrew stuffs.

This project uses Eclipse C/C++ for homebrew application development, and Citra 3DS emulator for homebrew debugging/testing.

### Purpose

Get the Console to be functional in 2 orientations, forward and reverse.

### Building

Since the Makefile is a bit customized, here is a table for specific `make` commands:

|Make commands|Action|Requirements|
|---|---|---|
|make all|Generates 3DSX and SMDH files.|Requires following [this wiki guide](https://github.com/wedr2/Guide/wiki/Setting-up-3DS-Homebrew-development-environment-using-Eclipse-CDT-for-C-and-CPP).|
|make cia|Generates 3DSX, CIA, and SMDH files.|Requires `makerom`|
|make sideload|Generates 3DSX file, then netloads to your Nintendo 3DS device.|Requires Homebrew Launcher v1.1.0|
|make citra|Generates 3DSX file, then launches the application via Citra emulator.|Requires Citra 3DS emulator. Make sure to change filepath in Makefile.|


### Results

Forward Orientation:

![](http://i.imgur.com/gz15sh3.png)

Reverse Orientation:

![](http://i.imgur.com/10rw5QP.png)

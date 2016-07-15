**Please read [wiki](https://github.com/tommai78101/homebrew/wiki) to see past progress and more information about this project.**   
**Everything uses open-source libraries to develop applications for Citra 3DS emulator, which is also open-source.**   

# Homebrew

Testing homebrew stuffs.

This project uses Eclipse C/C++ for homebrew application development, and Citra 3DS emulator for homebrew debugging/testing.

### Notes

* [Manual of Picasso Shader Lanuage for PICA200.](https://github.com/fincs/picasso/blob/master/Manual.md)

### Purpose

Added an actual floor, and make FPS camera be able to look up/down. 

Controls:

* Hold L to look around with directional pads.  
* Press any directional pads to move around.   
* Hold A to run/move quicker.   

### Results

Citra.exe (non-Qt) can now do Hardware Rendering. (This message will disappear in subsequent updates.)

![](http://i.imgur.com/0Pe7FMh.png)

### Building

Since the Makefile is a bit customized, here is a table for specific `make` commands:

|Make commands|Action|Requirements|
|---|---|---|
|make all|Generates 3DSX and SMDH files.|Requires following [this wiki guide](https://github.com/wedr2/Guide/wiki/Setting-up-3DS-Homebrew-development-environment-using-Eclipse-CDT-for-C-and-CPP).|
|make cia|Generates 3DSX, CIA, and SMDH files.|Requires `makerom`|
|make sideload|Generates 3DSX file, then netloads to your Nintendo 3DS device.|Requires Homebrew Launcher v1.1.0|
|make citra|Generates 3DSX file, then launches the application via Citra emulator.|Requires Citra 3DS emulator. Make sure to change filepath in Makefile.|


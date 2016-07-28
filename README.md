**Please read [wiki](https://github.com/tommai78101/homebrew/wiki) to see past progress and more information about this project.**   
**Everything uses open-source libraries to develop applications for Citra 3DS emulator, which is also open-source.**   

# Homebrew

Testing homebrew stuffs.

This project uses Eclipse C/C++ for homebrew application development, and Citra 3DS emulator for homebrew debugging/testing. Used Visual Studio 2015 for advanced debugging and refactoring code.

### Notes

* [Manual of Picasso Shader Lanuage for PICA200.](https://github.com/fincs/picasso/blob/master/Manual.md)

### Purpose

Implemented Entity-Component System and separated Player Camera View from Core Engine. Also, learned a lot of C++11 smart pointers usage.

Controls:

* Use touchscreen to look around. 
* Hold L and use C-Stick to look around.  
* Use C-Stick to move around.   
* Hold A to run/move quicker.   
* Press B to reverse Console orientation.
* Press Start to quit.

### Results

![](http://i.imgur.com/K63sUHe.png)

### Building

Since the Makefile is a bit customized, here is a table for specific `make` commands:

|Make commands|Action|Requirements|
|---|---|---|
|make all|Generates 3DSX and SMDH files.|Requires following [this wiki guide](https://github.com/wedr2/Guide/wiki/Setting-up-3DS-Homebrew-development-environment-using-Eclipse-CDT-for-C-and-CPP).|
|make cia|Generates 3DSX, CIA, and SMDH files.|Requires `makerom`|
|make sideload|Generates 3DSX file, then netloads to your Nintendo 3DS device.|Requires Homebrew Launcher v1.1.0|
|make citra|Generates 3DSX file, then launches the application via Citra emulator.|Requires Citra 3DS emulator. Make sure to change filepath in Makefile.|


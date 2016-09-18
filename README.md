TinyRayTracer
=============

[中文页面](README_zh.md)

# Introduction #

A simple implemention of ray tracing. Written by pure C++, without any 3rd library.

# Build #

## For Linux/Unix ##

```
cd TinyRayTracer
mkdir build
cd build
cmake ..
make
```

## For Windows ##

**Take Visual Studio as an example**

1. Make sure you have installed [cmake for windows](https://cmake.org/) and launch CMake-GUI.
2. Browse Source(Path of TinyRayTracer) and Browse Build(Destination path)
3. Click configure and Select Visual Studio on the popuped dialog.
4. Generate
5. The .sln will be located in the Destination path.

# Run #

## For Linux/Unix ##

```
cd ../bin
chmod +x tray #optional
./tray
```

## For Windows ##

Run the tray.exe in the TinyRayTracer/bin directory.


The tray program will read the file 'world.txt' and generate a **ppm** image file 'output.ppm', which can be opened by **xnview** or **photoshop** or any other ppm supported image viewer.
You can change the world.txt following the instruction.

Have fun :)

# Result #

![sample.jpg](bin/sample.jpg)
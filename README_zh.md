小小光线追踪器
==============

# 简介 #

一个光线追踪器的简单实现。使用纯C++语言，没有用到任何第三方库。

# 构建 #

## Linux/Unix用户 ##

```
cd TinyRayTracer
mkdir build
cd build
cmake ..
make
```

## Windows用户 ##

**以Visual Studio为例**

1. 安装好 [cmake for windows](https://cmake.org/)，并运行CMake-GUI。
2. Browse Source为TinyRayTracer的代码路径，Browse Build为目标工程生成路径。
3. 点击configure，弹出的对话框中选择Visual Studio。
4. 点击Generate
5. 目标工程文件夹内的.sln文件即VisualStudio的解决方案文件。

**注意：** 运行之前，最好用Release的方式编译，否则运行比较慢。

# 运行 #

## Linux/Unix用户 ##

```
cd ../bin
chmod +x tray #optional
./tray
```

## Windows用户 ##

运行TinyRayTracer/bin下的tray.exe文件。

tray.exe将会读取模型文件world.txt，经过光线追踪后，最终的效果图是同目录下名字为output.ppm的文件。PPM文件格式可以用一些主流的图片查看器比如Photoshop或者xnview打开，Ubuntu默认的图片查看器也支持ppm，Windows自带的图片查看器不支持。

之所以用PPM格式作为输出文件是因为PPM文件格式非常简单，不需要用到第三方图片库。

你也可以根据world.txt中的说明进行模型的修改。

:)

# 样例 #

![sample.jpg](bin/sample.jpg)
# NetworkModeling
Network Modeling and Analysis Project

### 1. 文件说明

- ppt文件夹：包括课堂演示的PPT
- doc文件夹：包括实验报告和代码说明文档两个pdf文件
- Release文件夹：包括可执行文件
- NerworkModeling文件夹：包括项目源代码

### 2. 编译说明

1. 请按照`doc/实验报告`中的编译环境进行编译
2. 代码检查：可使用`Microsoft Visual Studio`打开`.sln`文件，即可打开整个项目
3. 代码运行：请使用`Release`选项进行编译和运行

### 3. 噪声生成验证代码部分

1. 对于生成的噪声数据编写了`C++`和`python`文件来进行验证
2. 代码文件在`NetworkModeling/gaussian_verify`文件夹中
3. 运行时先单独执行`源.cpp`文件，此时会将噪声写入`data.txt`文件中
4. 然后运行`draw.py`文件，会读取`data.txt`文件，并生成直方图
# tinyrenderer课程

switch到了最初的版本并且删除了分支记录
从头开始构建自己的渲染器

## 项目构建

本项目在windows上开发，使用msys2的mingw64 + VSCode的CMake插件进行编译。
具体配置参考CMAkeLists.txt和.vscode文件夹中的设置。
设置中含有绝对路径，仅作参考，如需使用请自行根据环境更改。

## 备注

处理矩阵的基本运算对理解现代图形学的渲染管线无意义，因此引入了Eigen库来处理矩阵相关的操作。

# OpenGL魔方游戏

## 简介
学习OpenGL的时候出于兴趣打算写一个魔方小游戏，既可以熟悉OpenGL，又可以锻炼一下编程水平。由于水平有限，在具体的实现上可能不是很好。

## 进展
2月17号魔方游戏完成了1.0版本，实现了用户通过键盘鼠标旋转魔方的基本功能。

2月19号完成了2.0版本，重写了魔方的内部逻辑，v1.0采用逐面建模，v2.0采用逐块建模。v2.1在v2.0的基础上略作修改实现了转动动画效果。

## TODO：
1. 重写魔方类，进行模块化，使其可以构建各阶魔方
2. 添加游戏界面，包括简介和设置
3. 直接手写或者用人工智能的方法实现自动复原三阶魔方

## 编译
OpenGL的版本为3.3或更高版本，需要用到glfw3，glad和stb_image。具体的配置方法可以参考https://learnopengl-cn.github.io/01%20Getting%20started/02%20Creating%20a%20window/。

编译项目的方法参考https://www.glfw.org/docs/latest/build_guide.html。

### macOS
在macOS 10.15.3下安装了pkg-config后可以用下面的命令编译：
```
g++ `pkg-config --cflags glfw3` -o main main.cpp stb_image.cpp glad.c `pkg-config --static --libs glfw3`
```
### Windows
项目中的visual_studio_project可以用visual studio打开。
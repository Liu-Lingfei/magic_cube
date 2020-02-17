# OpenGL魔方游戏

## 简介
学习OpenGL的时候出于兴趣打算写一个魔方小游戏，既可以熟悉OpenGL，又可以锻炼一下编程水平。由于水平有限，在具体的实现上可能不是很好。

## 进展
2月17号魔方游戏完成了1.0版本，实现了用户通过键盘鼠标旋转魔方的基本功能。后面可能会有1.x小版本。

原计划实现的自动复原，感觉比较困难，我试试看，不一定能实现，如果实现了就是2.0版本。

## 编译
OpenGL的版本为3.3或更高版本，需要用到glfw3，glad和stb_image。具体的配置方法可以参考https://learnopengl-cn.github.io/01%20Getting%20started/02%20Creating%20a%20window/。编译项目的方法参考https://www.glfw.org/docs/latest/build_guide.html。

在macOS 10.15.3下安装了pkg-config后可以用下面的命令编译：
```
g++ `pkg-config --cflags glfw3` -o main main.cpp stb_image.cpp glad.c `pkg-config --static --libs glfw3`
```
# Five In A Row  

一个五子棋游戏，计划做成联网的那种，此项目是为了学习一些东西，所以代码结构可能有些糟糕了，毕竟也是很久之前做的，不过之后也可能会瞎JB写，这只是一个小工程，我想聚焦于学习的技术上（虽然这样做并不好..我还是收敛点吧）  

## 使用SDL2  

编译工程需要安装SDL2库，windows需要更改一下[Makefile](./Makefile)里面SDL_DIR的路径  

## 状况  

测试版 && 游戏逻辑正在计划开工 && ~~针对windows门派~~已加入Makefile在windows下编译  

## 编译  

```bash
make
make clean
```  

生成可执行文件`fiar.exe`（**f**ive **i**n **a** **r**ow）

## 非windows也可以这样运行(Ubuntu MacOS Linux)  

```bash  
$./run.sh
```  

效果如图所示：  
![five-in-a-row1](https://github.com/saiumr/saiumrImages/blob/master/five-in-a-row1.gif 'theme0')

你可以更改main.c中initPort()函数唯一参数初始化棋盘不同的主题 (鼓励修改和添加主题)：  
（这只是开发中这样修改，后面计划弄成gui列表那样）  
![five-in-a-row2](https://github.com/saiumr/saiumrImages/blob/master/five-in-a-row2.gif 'theme1')

## 其他的话  

我用了一个二维数组记录棋盘上可以落子的位置有没有棋子（0有1无），然后又用了一个一维数组记录了每个棋子该绘制的位置（圆心位置），以及是黑子还是白子...  

先写着吧，我感觉后面肯定得重写这部分结构  

I'm so stupid...  

and  

~~拒绝一切~~欢迎批评指正  

（真佩服几年前自己的脑回路）

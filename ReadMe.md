# Unix-like FileSystem 类Unix文件系统命令终端实现

### 文件目录说明：
1) UFS为源代码目录，该目录下有各种*.h和*.cpp文件，以及CMakeLists.txt。
2) build为可执行文件目录，包括可执行文件UFS.exe，必要的磁盘镜像文件*.img，及其他*.txt,history,passwd等其他依赖文件。
3) "操作系统课程设计报告（王德君组）.*"为课设报告的word版和pdf版。
4) compile demo.png为编译成功图片。
5) ReadMe.md(本文件)为目录、编译及运行说明文件。


### 源码编译方法：
- 注意：

  本说明适用于已安装CMake、MinGW的Windows环境，且编译前需确保UFS的绝对路径为纯英文路径；编译成功后需自己建一个passwd文件方能登录。

- 流程：

  在UFS目录下打开cmd窗口，新建文件夹build并cd进入，然后用cmd进到build目录下。
  执行cmake .. -G "MinGW Makefiles"即可编译该项目，可在build下生成UFS.exe的可执行文件。

  总结如下：

```
cd UFS
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
make
```

- 编译成功示例：

  <img src="https://raw.githubusercontent.com/SeaEagleI/UFS/master/pics/compile%20demo.png">

### 直接运行方法：

直接双击build目录下的UFS.exe文件即可，passwd文件中明文存储了各用户密码对<user,password>。
对某个命令有疑问可以使用man命令获得帮助，如"man mkdir"。

### 参考

- https://github.com/BaiJiazm/FileSystem
- https://gitee.com/solym/UNIX_V6PP

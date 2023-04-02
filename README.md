# 🌋火山视窗 - PIV模块



## 💽 安装

下载地址：https://saier.lanzoul.com/b016cwvle

安装本模块前，必须将 [火山软件开发平台](http://www.voldp.com/) 更新到最新版本，**及时安装论坛的更新包才是最新版**。

本模块部分功能需要 VS 2017 以上才能编译使用。

现在提供两种形式的安装包：

- ##### 火山模块安装包 [.vcip]

  **模块本体的安装包。**

  火山自身的模块安装包格式，双击 `.vcip` 文件即可打开火山程序进行安装，但压缩率比较低。

  如果安装失败，请对火山主程序按鼠标右键打开「属性」，勾选「兼容性」选项卡里的「以管理员身份运行此程序」。

- ##### 可执行安装文件 [.exe]

  仅**PIV静态库**使用这种安装包。

  使用 [Inno Setup 6](https://jrsoftware.org/isinfo.php) 打包，压缩率比较高，自动检测安装路径，本安装包为便携式安装，无注册表写入和卸载程序。




## 🎯 简介

本模块总共有三个子模块，三个子模块之间功能不重叠，主要是收录标准有以下差别：

- **PIV基础类**

  除了视窗基本类，不依赖其他任何模块。

- **PIV扩展类**

  会依赖部分官方模块，但不会依赖MFC界面和其他第三方模块。
  
- **PIV静态库**

  由于 lib 静态库占用的体积比较大，特别增加本子模块，需要携带静态库的类库均已移动到该子模块。

本模块封装遵从以下标准：

- **不重复造轮子**

  核心库已有的功能，如果没有可明显改进的地方，不会重复封装。

- **开源**

  所有封装的代码均公开源码。

- **效率优先**

  以执行效率为优先，基本使用C++和嵌入式语法封装。

- **源码编译**

  能直接用源码编译的库，就不会编译成 dll 再封装，缺点是会增加编译耗时，如果其他代码出错，可能会一下子蹦出大量报错。

- **面向对象**

  关联性的功能封装成类，以类实例使用。除了常用命令，尽量减少使用全局类，以「类名.静态方法」调用，减少同名冲突。
  
- ~~**解耦**~~

  ~~减少不同类库之间的互相依赖，能以最小的代价把类库抠出来单独使用。~~
  
  随着基础功能的广泛应用，类库之间耦合度增大，已经难以解耦了。

**PIV** 是什么意思？

> 我也不知道，这是我几年前注册新域名的时候，试出来的三个字母，拼凑的思路上比较靠近 pic、pixiv。
>
> 刚有人说倒过来就是 VIP，我还真没想到。这里说一下，PIV模块以后会一直免费开源，不会出 VIP 版。
>



## 📝 更新日志

 详细的更新日志，请看 [完整文档](README_CN.md)




## 💌 开源项目

- [nlohmann **JSON**](https://github.com/nlohmann/json) `3.11.2` `MIT license`  一个现代 C++ 的 JSON 库
- **[fmtlog](https://github.com/MengRao/fmtlog)**  `2.2.1`  `MIT license` 一个纳秒级精度的高性能异步日志记录库
- **[{fmt}](https://github.com/fmtlib/fmt)**  `9.1.0`  `MIT license` 格式化文本库，std::format 的实现 
- **[md4c](https://github.com/mity/md4c)** `0.4.8`  `MIT license` 一个 CommonMark 0.30 规范 + GFM 的 Markdown 解析库
- **[simpleini](https://github.com/brofield/simpleini)** `4.19` `MIT license` 简易的 INI 配置文件读写库
- **[simdutf](https://github.com/simdutf/simdutf)** `3.2.3` ` Apache-2.0, MIT license`  使用 SIMD 指令集加速，每秒数十亿字符的Unicode编码验证和转换库
- **[OpenCC](https://github.com/BYVoid/OpenCC)** `1.1.4` `Apache-2.0 license` 中文简繁转换开源项目，支持词汇级别的转换、异体字转换和地区习惯用词转换
- **[bit7z](https://github.com/rikyoz/bit7z)** `4.0.0-RC` `Mozilla Public License v2.0` 7-zip的封装类
- **[7-zip](https://www.7-zip.org/)** `22.01` `GNU LGPL license` 完全免费而且开源的压缩软件（采用GNU LGPL协议，只使用它的 dll 文件不会传染）
- **[MinHook](https://github.com/TsudaKageyu/minhook)** `1.3.3` `BSD-2-Clause License` 一个简约的 x86/x64 API Hook 库
- **[MMKV](https://github.com/Tencent/MMKV)** `1.2.14` `BSD-3-Clause License` 腾讯的高性能键值表

※本模块封装的开源项目均采用较宽松的开源协议，如 MIT、BSD、MPLv2 ……



## 🧰 闭源项目

本模块封装了以下闭源项目：

- **[BASS](http://www.un4seen.com)** `2.4`  音频播放支持库

  可以在非盈利软件中免费使用，商用需要购买许可证

- **[VMProtect](https://vmpsoft.com)** `3.7.2`  软件加密壳

  需要购买正版才能正常使用


# 🌋火山PC - PIV模块



> 👨🏻‍💻作者: Xelloss
>
> 🔗网址: https://piv.ink/volpiv
>
> 📧邮箱: xelloss@vip.qq.com



## 📢

之前我单独公开了几个库，维护起来甚是麻烦，现在我把自用的模块整理分享出来，以后有什么新功能，基本就在这里更新了。

如果遇到bug和模块冲突，欢迎找我报错，最好带上例子。



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

  使用 [Inno Setup 6](https://jrsoftware.org/isinfo.php) 打包，压缩率比较高，自动检测安装路径。

  便携式安装，无注册表写入和卸载程序，打包脚本已在压缩包中提供。



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

- **源码优先**

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

※我经常反复修改已封装好的代码，比如修正bug、优化效率、规范格式、修订备注等，但如果功能和用法没有改变，一般不会写在更新日志里，所以每次更新改动的地方其实还是有不少的。

### 📅 2023/02/20

1. 修正线程池类的两处bug

### 📅 2023/02/19

1. 「简易HOOK类/多重HOOK类」改为使用源码编译。
2. 修正部分代码错误，主要影响 PivJSON

### 📅 2023/02/17

1. 拆分子模块「**PIV静态库**」，将 bit7z 和 MMKV 等体积较大的静态库移动到该子模块，主体模块的体积再次缩减到几十MB内。

2. 更新了 bit7z，用最新源码重新编译了，应该修复了某些情况下可能出现的编译错误，32 位下压缩失败的原因已查明，不开启进度回调就可以了。
3. 优化「标准文本类」、「文本视图类」，增加更多功能。
4. 重构「PivJSON」，支持更多文本类型，合并和调整部分方法。
5. 新增「表单构造类」、「表单构造类U」、「表单构造类A」，用于快捷填写网络POST请求的表单参数，其中 UTF-8 编码的「表单构造类U」最常用。
6. 新增「表单解析类」、「表单解析类U」、「表单解析类A」，用于在服务端解析POST的表单参数。
7. 新增「URL地址构造类」，用于快捷创建经过URL编码的地址。
8. 「线程池类」、「线程池类EX」现在支持在暂停状态下清空任务，修改了销毁的默认值，优化内部代码。
9. 优化了URL编解码

### 📅 2023/01/19

1. 新增「文本视图类」、「文本视图类U」和「文本视图类A」，封装了对应 Unicode、UTF-8 和 ANSI 编码的 std::basic_string_view。

   文本视图本身不拥有文本数据，而是引用其他文本的字符缓冲区，因此使用文本视图不会复制文本数据，速度极高，缺点是不能通过视图修改文本数据。

2. 新增「文本视图容器类」、「文本视图容器类U」和「文本视图容器类A」，为对应文本视图的数组类（基于std::vector实现）。

3. 优化重构「标准文本类」（std::basic_string），实现了官方文本类中的大部分功能。

4. 新增对应 UTF-8 和 ANSI 编码的「标准文本类U」和「标准文本类A」，以及新增对应的数组类「标准文本容器类U」和「标准文本容器类A」。

5. 新增「纳秒时钟类」，这是「格式日志类」中的同款时钟，能获取 1 纳秒级精度的时间戳（Windows API 最高只支持 100 纳秒精度），但用起来比较麻烦，需要在后台定期校准时间，有高精度要求才用吧。

6. 「VMProtect」类新增「保护」、「虚拟化保护」、「变异保护」、「超级保护」、「虚拟化保护\_锁定序列号」、「超级保护\_锁定序列号」等方法，与之前的区别是可以自定义标记名称。

7. 优化重构「URL地址解析类」，基于文本视图提升了解析速度。

8. 「通用文件对话框」增加参数「不改变目录」。

9. 「BASS音频类」的「取所有设备信息」和「取所有录制设备信息」，不再跳过设备号0，所以用法和例子有所改变。

10. 修正多处 bug

### 📅 2022/12/15

1. 修正「simdutf」编码转换的两处代码错误

### 📅 2022/12/13

1. 适配火山12-12的更新，所有静态库已经同时支持MT和MD版，也就是项目属性是否开启「使用静态C++运行时库」都能正常编译
2. 删除全局方法「十六进制文本到整数」和「十六进制文本到长整数」，因为最新版本的视窗基本类已经提供了同名方法
3. 修正多处 bug

### 📅 2022/12/03

1. 修复上一版导致的一些 bug 和模块冲突（新库继续慢慢磨）

### 📅 2022/11/25

1. 优化 Unicode 编码转换逻辑，PivJson、MMKV 等需要 Unicode 编码转换的库，默认使用系统 API 转码，如果项目编译了 simdutf，就自动切换为使用 simdutf 转码。

   现在避免了跟火山模块冲突，因为火山模块也有 simdutf，两个模块同时编译一样的 cpp 源码会报错。

2. 将「进程操作类」的嵌入语句全部转移到 C++ 文件中，并修正部分问题。

3. 移除bit7z的 VS 2015 静态库，因为 VS 2015 不支持火山的文本哈希表。

### 📅 2022/11/18

1. 新增「MMKV键值表」，重新封装了腾讯MMKV，跟官方的相比：
   - 完全开源，使用静态库编译，不带dll
   - 封装了所有能封装的功能，支持存取更多值类型
   - 更完善的备注（吐槽一下腾讯的开源质量，注释太少甚至没有）
2. 修正「格式日志类」不兼容Windows 7 SDK的问题，增加方法「加入来源日志」用于处理「MMKV日志事件类」的日志
3. 其他优化
4. 火山模块安装包的压缩率太低，增加EXE版安装包（体积缩减一半以上）
   - 火山模块安装包：PIV模块[2022-11-18]\[vcip].zip
   - 可执行安装文件：PIV模块[2022-11-18]\[exe].zip
   - 可执行安装文件使用 Inno Setup 6 打包，便携式安装（无注册表写入和卸载程序），所使用的脚本已包含在压缩包中


### 📅 2022/11/10

1. 重构JSON库
   - 新增「PivJSON」和「PivOrderJSON」，移除「nmJson」和「nmOrderJson」
   - 调整了大量的方法和参数，旧项目不想改动的话，可以安装 kyozy 封装的 [**nlohmann json 解析库**](https://bbs.125.la/thread-14698393-1-6.html)
   - 使用 simdutf 加速 Unicode 的编码转换，修订注释，完善功能的封装
2. 「simdUTF」的部分方法增加后缀为「\_Ex」的版本，区别是在参数中返回转换后的文本数据，在某些情况下可以减少内存分配
3. WinHTTP的网络异步访问类增加一个「用户数据」参数，用于标识访问来源或传递指针
4. 将WinHTTP嵌入语句的部分常量名改成数值，以兼容旧版本的Windows SDK（起码7.0以上）
5. 其他优化和修正

### 📅 2022/10/31

1. simdutf的源码更新至2.0.2并重构，新增「simdUTF」，删除「SIMDUTF编码库」
2. 修正了无论是否使用bit7z都附带7z.dll的问题，原因是我定义了一个模板基础类，模板基础类会被强制解析，连带写在包名的头文件、附属文件之类也生效了
3. WinHTTP网页访问返回的Cookies现在包含了重定向过程中的Cookies，「网络请求响应类」增加一个方法「取合并Cookies」

### 📅 2022/10/30

1. 增加「简易HOOK类」和「多重HOOK类」，封装了GitHub上非常热门的一个Inline Hook库
2. 修正「配置文件操作类」的数个 BUG
3. 修正bit7z的部分问题，由于之前的参数设置错误，重新编译了bit7z的静态库
4. 更新例程

### 📅 2022/10/29

1. 封装了基于 7z.dll 的 C++ 包装类 bit7z，火山目前最强的文件压缩和解压类库，支持 7-zip 程序的所有格式和基本功能。
   - 存档读写类：简易版的封装，只需要执行一个方法就能压缩和解压文件
   - 存档解压类：功能完备的解压类，除了解压外可以读取压缩包里的各种信息和属性，支持解压进度反馈
   - 存档压缩类：功能完备的压缩类，可以设置所有的压缩选项，支持压缩进度反馈
   - 存档编辑类：在压缩类上增加了压缩文件编辑功能，可以对压缩包的项目进行[改名/更新/删除]等操作
   - 未封装文件流读写的相关方法，过一两个版本解决
   
2. 优化「格式日志类」：
   - 魔改了 fmtlog 的源码，将内部编码从 UTF-8 改为 UTF-16LE，不再需要进行编码转换，大幅增加效率
   - 输出的日志文件从 UTF-8 编码改为 UTF-16LE，请注意别把日志写到旧版的文件后面
   - 增加「加入文本日志、加入文本日志_间隔」，用于添加不进行格式化的文本内容
3. 优化「线程池类」和「线程池类EX」：
   - 增加方法「是否需要退出」，用于在销毁线程池时通知线程应该尽快结束
   - 「线程池类EX」增加属性读写方法「动态线程周期」，用于后续更改动态调整线程数量的周期时间
   - 调整源码结构，优化事件流程，修复调试版销毁线程池时容易与窗口事件冲突的问题
4. 新增类「数组P」，提供一些增强的数组操作，部分参考了龙纹的「FP函数扩展」模块
5. 「文本P」增加多字节数组到文本、UTF8字节数组到文本
6. 其他多处优化和修正

### 📅 2022/09/16

1. 增加类「文本P」，「文本处理类」中的全局方法已标记为弃用
   因此**必须将火山更新到飞扬#21 09-15或更新的版本**
2. 增加类「编码P」，为「编码辅助类」的别名
3. fmt 的源码更新到 9.1.0、fmtlog 更新到 2.2.1
4. 修正「格式日志类」在盘符路径创建日志文件失败的问题
5. 其他细微修正与优化


### 📅 2022/08/22

1. 文本处理类增加全局方法：整数到中文小写数字、整数到中文大写数字、小数到中文小写数字、小数到中文大写数字、小数到中文小写金额、小数到中文大写金额
2. 编码辅助类增加全局方法「取整数值位数」，可计算整数值的十进制位数，比如10000返回5位。

### 📅 2022/08/18

1. 「网络同步访问类」、「网络异步访问类」等增加成员变量「是否编码网址」，用于控制是否在访问类的内部对网址进行 URL 编码，默认为假。
2. 调整「文本\_取文本中间」的参数
3. 其他多处细微优化和修正

### 📅 2022/07/26

1. 新增「简易加解密」，纯 C++ 源码实现，支持 AES、DES、RC4、MD5、SHA1、SHA256、SHA512 几个算法。其中 RC4 支持不固定长度的密码，可以获得与易语言一致的加解密结果。

### 📅 2022/07/25

1. 新增全局类「SIMDUTF编码库」，提供高速的 Unicode 验证和编码转换支持（UTF-8、UTF-16LE、UTF-32LE互转），64 位比火山核心库快几倍，32 位仍有微弱优势，但不支持 Unicode 与 ANSCII 互转
   本模块中编码转换需求较多的类库将逐步改为使用「SIMDUTF编码库」
2. 新增「OpenCC简繁转换类」，提供词汇级别的本地中文简繁转换
3. 新增全局类「BASE编解码类」：字节集到BASE91文本、BASE91文本到字节集、字节集到BASE85文本、BASE85文本到字节集
   BASE91 相比 BASE64 节省了 10% 到 19% 的长度，BASE64请用字节集类自带的，自测速度最快，何必用第三方的来DeBuff
4. 「标准随机数类」增加方法：取随机字符、取随机汉字、取随机字节集
5. 修正 fmt 与「炫彩界面支持库」冲突的问题
6. 修改部分C++源码的文件名，解决不同模块间的重名冲突

### 📅 2022/07/15

1. WinHTTP 相关类库的「网页访问」增加两个参数，在内部对 POST 的提交数据进行 URL 编码（默认不编码）
2. 修正「配置文件操作类」的部分方法
3. 其他修正

### 📅 2022/07/08

1. 修正「CNG加解密.密钥派生函数」会崩溃的问题
2. 「快捷方式解析类」改名为「快捷方式操作」，并修复大量问题
3. 新增「全局内存管理类」和「本地内存管理类」，开销较大，一般不建议使用，只用来释放系统API或某些DLL申请的全局或本地内存。
4. 新增全局方法「取千位分隔数值文本」
5. 「标准时间类」新增方法「置文件时间」和「到文件时间」，可以转换FILETIME结构体的时间
6. 重新梳理测试，修复和优化调整多处代码

### 📅 2022/07/05

1. 新增「WinHTTP网络类」，完整封装了WinHTTP，面向精通 HTTP 协议的开发者
2. 新增「网络同步访问类」，面向普通用户的 WinHTTP 二次封装，用法跟官方 Curl 的「网络访问类」一样
3. 新增「网络异步访问类」，面向普通用户的 WinHTTP 二次封装，提供异步的并发式网络访问
4. 新增「网络同步访问类EX」和「网络异步访问类EX」，EX版加了自写的持久 Cookie 管理
5. 「格式日志类」的源码更新到 fmtlog 2.2.0
6. 新增「对象容器类」和「对象容器模板类」
7. 新增类方法「标准时间类.置格林威治时间」
8. 新增全局方法「写文本数组注册项」和「取文本数组注册项」
9. 调整「高并发网络访问类」的部分方法和参数
10. 修正若干错误

### 📅 2022/06/14

1. 修正和优化「URL编解码类」

### 📅 2022/06/13

1. 「CNG加解密」增加了下列返回字节集型哈希值的方法：
   取数据HMAC\_MD5\_字节集、取数据HMAC\_MD4\_字节集、取数据HMAC\_MD2\_字节集、取数据HMAC\_SHA1\_字节集、取数据HMAC\_SHA256\_字节集、取数据HMAC\_SHA384\_字节集、取数据HMAC\_SHA512\_字节集
2. 修正了「CNG加解密」中 RC4 算法加解密失败的问题
3. 修正了「CNG加解密」解密所得字节集类的尾部，可能有冗余 0 数据的问题

### 📅 2022/06/08

1. 修正「格式日志类.打开每日日志」的日期错误，增加「日期格式」参数，可以自定义每日日志文件名中的日期格式
2. 格式日志类运行时不再独占日志文件
3. 增加全局方法「小数向上取整」
4. 修正「线程池类」和「线程池类EX」中「是否空闲」的封装错误

### 📅 2022/06/05

1. 增加「标准随机数类」对象类，及「随机数类\_xxx」等一系列不同随机数算法的对象类，为\<std::random\>的封装，可以产生高质量的伪随机数
2. 增加「配置文件操作类」，提供简易的 ini 配置文件读写操作，支持多字节、UTF8和UTF-16LE编码
3. 增加全局方法「取标准格式文本U8」，能正确处理\<std::format\>的汉字填充对齐
4. 增加全局方法「创建数值型数组类」和「创建文本型数组类」
5. 「连续加入××」改名「数组连续加入XX」

### 📅 2022/05/30

相对于之前单独发布的版本，有以下重要更新：

- **BASS音频库**
  1. 将 dll 文件更新到最新版
  2. 调整「BASS音频类.录制回调」事件的返回值，现在是返回0为继续录制，请注意修改源码
- **格式日志类**（fmtlog）
  1. 优化代码，减少非必要的编码转换，降低性能损失
  2. 日志文件名现在支持 Unicode 了


- **CNG加解密**
  1. 调整类名，避免跟仰望火山模块冲突
  2. 将加解密失败后返回原数据，改为返回空字节集
  3. 屏蔽「CNG加解密.解密\_RSA\_公钥」，因为 CNG 的 RSA 公钥不能用来解密
  4. 将「CNG_填充方式.对称\_块填充」改名为「对称\_PKCS7」


- **高并发网络访问类**
  1. 优化请求信息的提交，提交 JSON 数据时自动加入相关请求头
  2. 优化代码结构，减少使用「读指针处对象」
  3. 所有事件回调中的「对象指针」改为「传输对象」
- **时钟队列类**
  
  1. 弃用自增的时钟序号，改为添加时钟时由用户自定义「时钟标记」
- **其他**（大量未发布过的新内容，这里就不一一列举了）




## 💌 开源项目

- [nlohmann **JSON**](https://github.com/nlohmann/json) `3.11.2` `MIT license`  一个现代 C++ 的 JSON 库
- **[fmtlog](https://github.com/MengRao/fmtlog)**  `2.2.1`  `MIT license` 一个纳秒级精度的高性能异步日志记录库
- **[{fmt}](https://github.com/fmtlib/fmt)**  `9.1.0`  `MIT license` 格式化文本库，std::format 的实现 
- **[md4c](https://github.com/mity/md4c)** `0.4.8`  `MIT license` 一个 CommonMark 0.30 规范 + GFM 的 Markdown 解析库
- **[simpleini](https://github.com/brofield/simpleini)** `4.19` `MIT license` 简易的 INI 配置文件读写库
- **[simdutf](https://github.com/simdutf/simdutf)** `3.3.0` ` Apache-2.0, MIT license`  使用 SIMD 指令集加速，每秒数十亿字符的Unicode编码验证和转换库
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


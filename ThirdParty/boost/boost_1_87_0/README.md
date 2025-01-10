## Windows

通过开始菜单打开 VC 环境, 或

```
%comspec% /k "I:\D\HenDuoDongXi\Vs2022\Installed\VC\Auxiliary\Build\vcvars64.bat"
```

在源码根目录中执行

```
cd boost_1_87_0

bootstrap.bat msvc

b2 address-model=64 link=static runtime-link=shared threading=multi --build-type=complete --prefix=../Installed stage install
```

以上构建命令为生成静态库, 输出到目录 stage\lib 中, 安装到 b2 工作目录的 ../Installed 中
通常静态库的链接方式更友好, 是自动的, 提供 lib 搜索路径即可
boost 的静态库文件名在 Windows 下也以 lib 开头

### 其它构建形式的示例

#### 动态库, Debug, Release

须在项目加宏定义 BOOST_ALL_NO_LIB, 以屏蔽自动静态链接, 否则可能看到链接相关的错误, 如 "打不开 libboost_filesystem_..."

```
b2 address-model=64 link=shared runtime-link=shared threading=multi --build-type=complete stage
```

#### 动态库, Release

```
b2 address-model=64 variant=release link=shared runtime-link=shared threading=multi --build-type=complete stage
```

## Ubuntu

```
cd boost_1_87_0

./bootstrap.sh gcc

./b2 address-model=64 link=static runtime-link=shared threading=multi --prefix=../Installed stage install
```

## 安装

注: 在 stage 后加 install 即可安装到默认的 C:\Windows, 也可指定安装前缀, 如

```
b2 address-model=64 link=shared runtime-link=shared threading=multi --build-type=complete --prefix=../Installed stage install
```

## 接入 cmake 项目

对于使用 cmake 接入, 由于 boost 的静态链接是自动的, 且文件名复杂, 应考虑使用 stage\lib\cmake 中的帮助 cmake 进行链接

## 构建正确性验证

```
cd ..
mkdir ExampleBuild
cd ExampleBuild
cmake ..

cmake --build . --config Debug
cmake --build . --config Release
cd ..
ExampleBuild\Debug\BoostExample.exe
ExampleBuild\Release\BoostExample.exe

```


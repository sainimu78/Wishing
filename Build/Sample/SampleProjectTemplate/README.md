## 修改 Build 目录中的项目目录名

```
Wishing\Build\Sample\SampleProjectTemplate
```

## 修改平台脚本中的 `ProjectName`

Windows

```
Wishing\Build\Sample\SampleProjectTemplate\Windows\Setup.bat
Wishing\Build\Sample\SampleProjectTemplate\Windows\Update.bat
Wishing\Build\Sample\SampleProjectTemplate\Windows\Release.bat
```

Linux

```
Wishing\Build\Sample\SampleProjectTemplate\Linux\Setup.sh
Wishing\Build\Sample\SampleProjectTemplate\Linux\Update.sh
Wishing\Build\Sample\SampleProjectTemplate\Linux\Release.sh
```

## 修改 Project 目录中对应的 CMake 脚本目录名

```
Wishing\Project\Sample\SampleProjectTemplate
```

## 修改 `ProjectName`

```
Wishing\Project\Sample\SampleProjectTemplate\CMakeLists.txt
```

## 修改 Source 目录中对应的源码目录名

```
Wishing\Source\Sample\SampleProjectTemplate
```

## 构建与发布

Windows

```
cd Windows
Generate.bat
Build.bat
Install.bat
Release.bat
explorer F:\sainimu78_Storage\Release\Windows
```

Linux

```
cd Linux
./Generate.sh
./Build.sh
./Install.sh
./Release.sh
```


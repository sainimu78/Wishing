set INCLUDE=D:\HenDuoDongXi\Vs2022\VC\Tools\MSVC\14.33.31629\include;C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\ucrt;C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\um;C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\shared
set LIB=D:\HenDuoDongXi\Vs2022\VC\Tools\MSVC\14.33.31629\lib\x64;C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x64;C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\ucrt\x64
set PATH=D:\HenDuoDongXi\Vs2022\VC\Tools\MSVC\14.33.31629\bin\Hostx64\x64;%PATH%
mkdir out
cl /DWIN32 /EHsc /I.\ /Fo"out/" /Fe"out/a.exe" a.cpp Util\MyCmd.cpp
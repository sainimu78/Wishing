ftp_download.bat

```
@echo off
ftp -s:info.txt
```

info.txt

```
open 111.11.111.11
admin
1234
binary
prompt
;cd /ThirdPartySource/llvm-project/llvm-project/build/Windows/x64/Release/bin
mget /ThirdPartySource/llvm-project/llvm-project/build/Windows/x64/Release/bin/libclang.dll
bye
```


## github

https://github.com/llvm/llvm-project.git

```
git clone git@github.com:llvm/llvm-project.git
```

## Branch Name

Branch_llvmorg-17.0.6

## SHA-1

6009708b4367171ccdbf4b5905cb6a803753fe18

## Command Build libclang on Ubuntu

Debug

```bash
cmake -S llvm -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=ON -DLLVM_ENABLE_PROJECTS="clang"

ninja -C build libclang
```


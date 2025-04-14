set path=I:\D\HenDuoDongXi\LLVM\Installed\LLVM\bin;%path%
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_CXX_COMPILER="clang++.exe" -DCMAKE_LINKER="lld-link.exe" ..
cmake --build .
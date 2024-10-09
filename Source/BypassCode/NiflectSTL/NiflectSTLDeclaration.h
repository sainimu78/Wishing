#pragma once
//本文件用于生成代码时旁路STL头文件, 可大幅减少解析耗时, 依此思路还可旁路其它内容多的头文件
//现STL旁路文件无后缀, 不会被CMake加入, 如使用有后缀的旁路文件则需要在CMake中屏蔽或将BypassCode移到别的位置避免被CMake加入到工程
//优化阶段可考虑实现一种STL简化工具, 自动生成旁路代码
//现手工修改步骤:
//1. 解析出现错误信息, 观察找出引起问题的STL头文件名, 
//2. 复制BypassCode/iflectSTL目录中的任意文件, 将文件名改为找到的STL头文件名
//3. 在本文件中移植相应的定义, 只需要设法定义空的STL定义, 令声明处可编译即可, 具体定义请参考VC的STL
//4. 如原本的STL头文件内容在展开include后内容不多或移植定义太繁琐, 也可在本文件中直接include, 修改后测试解析耗时, 如无法接受或希望优化, 则将必要的定义简化移植到本文件中
//5. 由于手工修改, 可能修改内容本身不合语法, 在解析时也会有相应的提示, 需要注意查看错误信息
#include <xmemory>
#include <string>
#include <vector>
#include <type_traits>
#include <utility>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

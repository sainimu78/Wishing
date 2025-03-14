# 五星

五星是一款内容编辑器开发框架

# 特性

- 使用 C++ 和 CMake 开发
- [Niflect](https://github.com/sainimu78/Niflect), C++ 原生风格反射
- 具引用关系的内容文件管理
- 内容编辑和有效性更新流程
- 编辑器到运行时的内容 Cook 流程
- 现代动画元素控件
- 基于模块化 C++ 脚本的迭代开发体验
- Windows 和 Ubuntu 下桌面产品的打包流程

# 期望应用案例

- 游戏开发工作流
- 基于下一代资源管理方案的演示文稿 (PPT)
- 视频或图像后处理应用

# 研发目标

内容编辑产品通常具一些系统和功能方面的共性，这些共性通常实现困难，如：

- 互相引用的内容文件
- 内容编辑完成后的 Cook 流程
  - Cook 是指将内容文件转换为更简单、更紧凑的数据格式的过程。
  - 用于提高运行时应用程序的加载和序列化效率。
- 编辑实例属性或内容的有效性更新流程
- 多用户协同内容编辑

因此，五星旨在标准化内容编辑产品的开发过程
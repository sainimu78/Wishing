此为非官方版本, 从引擎课Picolo项目中复制, 官方github: https://github.com/no1msd/mstch
Picolo版本与官方最新版本差异巨大, 官方版本依赖 boost/variant.hpp, 如果用no_boost的分支, 则依赖std::variant, c++14不支持
该版本已略作修改以支持指定使用的字符串类型
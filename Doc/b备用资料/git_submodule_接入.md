# 用乌龟添加 submodule

或

```
git submodule add git@github.com:sainimu78/CMakeProjectFramework.git F:\Fts\Proj\Test\Niflect\ThirdParty\CMakeProjectFramework
```

# 主 git checkout/pull 之后 clone 子模块

clone 后须 切到某个分支, 如切到主分支

```
git submodule update --init --recursive
git checkout main
```


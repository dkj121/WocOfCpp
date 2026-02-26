# README FOR COUNTER

---

## 可执行文件

[counter.exe](ElementaryPart/counter/out/build/myCounter/counter.exe)

---

## 执行样例

![样例](../../Asset/Snipaste_2026-02-24_11-16-08.jpg)

---

## Quick Start

当‘>’出现，证明程序正常运行
对多字符关键字不支持去除字符之间的空格
对于函数定义固定使用fun(x) = …… ~~（自己都忘了两次）~~
建议按Ctrl + C结束程序

---

## 实现内容

- [x] 支持基本四则运算：+, -, *, /
- [x] 支持括号 () 改变优先级
- [x] 支持负数和正数前缀：-5, +3
- [x] 支持幂运算：^ 或 **
- [x] 支持取模运算：%
- [x] 正确处理运算符优先级和结合性
- [x] 提供清晰的错误提示
- [x] 支持变量定义和使用
- [x] 支持内置数学函数：sin, cos, tan, sqrt, abs, log, ln, exp
- [x] 支持数学常量：pi, e
- [x] 支持比较运算符：>, <, >=, <=, ==, !=
- [x] 支持逻辑运算符：&&, ||, !
- [x] 支持用户自定义函数 （ **仅实现了单个函数fun的记录** ）
- [ ] 支持条件表达式：condition ? true_value : false_value
- [ ] 实现符号求导功能
- [ ] 支持复数运算
- [ ] 实现 REPL 交互界面，支持历史记录

---

## 技术栈

CMake, gcc  ~~ChatGPT 5.2~~

---

## 开发环境

Windows11

---

## 参考文献

对于整体上的结构设计参考了[《craftinginterpreters》](https://craftinginterpreters.com/)。

对于排版使用clang-format大刀阔斧的修改成了Google标准。

对于Calculators中有关调度场算法的代码基本上由伟大的ChatGPT实现~~（啥子ChatGPT天天就知道预设功能）~~，而注释则大都用Tab+肉眼识别~~（啥子Tab天天说些没用的）~~。

---

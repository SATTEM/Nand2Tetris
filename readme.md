# Nand2Tetris课程作业实现
## 基本信息
- 课程链接:[第一部分](www.coursera.org/learn/build-a-computer) [第二部分](https://www.coursera.org/learn/nand2tetris2)
- 语言(实现语言):C/C++
## 测试方法
- 所有编程项目都可以执行以下代码进行编译，结果均在对应项目的bin文件夹中
  ```sh
  mkdir build && cd build
  cmake ..
  make
  ```
  
- 各编译器的使用方法如下
  ```sh
  XXXCompiler input.yyy #输出input.zzz
  #XXX为输入语言，如VMCompiler
  #yyy为输入语言对应的后缀(jack/vm/asm)
  #zzz为输出语言对应的后缀(vm/asm/hack)
  ```
## 导航
1. [基本逻辑元件](/PartI/proj1/)
2. [基本计算元件](/PartI/proj2/)
3. [基本存储元件](/PartI/proj3/)
4. [Hack汇编语言](/PartI/week4)
5. [实现计算机](/PartI/proj5)
6. [实现汇编器](/PartI/proj6/)
7. [实现VM码编译汇编码](/PartII/VMCompiler/)
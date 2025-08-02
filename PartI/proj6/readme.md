# 使用方法
- 编译
```shell
mkdir build
cd build
cmake .. && cmake --build .
```
- 运行
```shell
HackAssembler input output #将hack汇编文件input编译为机器码，输出到output
```
> 可用diff file1 file2来比对两个文件，以检验编译结果是否正确
# 已知问题
汇编器不能正确识别中间带空格的C指令：
在线IDE未解决此问题，其认为M = 1为非法指令，且D M=1为两条C指令
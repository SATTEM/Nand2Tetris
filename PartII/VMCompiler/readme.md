# 实现VM码编译为汇编码
> - 假设输入均符合规范
> - 对于static内存段，编译器行为与课程标准不同，生成的变量名会在开头多一个F，以防止由于vm文件以数字开头导致的错误
- [初始化与退出](#preset)
- [内存操作](#memory)
	- [push](#push)
	- [pop](#pop)
- [一般操作](#universal)
	- [not/neg](#sole)
	- [add/sub/and/or](#2op)
	- [eq/gt/lt](#2cp)
- [实现技术](#trick)
## 初始化和退出<a id="preset"></a>
- 在正式执行任何汇编代码之前，需要规定个内存区段的位置，即设置RAM中指示内存区段的单元为正确的值(主要是SP)

	根据标准映射，代码如下:
	```hack
	@256
	D=A
	@SP
	M=D //栈的第一个内存地址为256
	```
- 在程序完成任务后，需要进入循环防止意外执行其它代码
  ```hack
  (END)
	@END
	0;JMP
  ```
## 内存操作<a id="memory"></a>
- ```push segment i //将seg[i]压入栈顶```<a id="push"></a>
  示例代码如下:
  	```hack
	//push argument i
	//将argument[i]压入栈，并令SP++
	@i //i实际上是任一整数
	D=A //D=i
	@ARG
	A=D+M //偏移到argument[i]
	D=M //D=argument[i]
	@SP
	A=M //前往栈
	M=D //压入栈中
	@SP
	M=M+1 //SP++
	```
- ```pop segment i //弹出栈顶元素到seg[i]```<a id="pop"></a>
  	示例代码如下:
	```hack
	//pop local 1
	//将栈顶元素弹出到局部第2个变量
	@1
	D=A //偏移量
	@ARG
	D=D+M //记录argument[1]的地址
	@addr
	M=D //存储记录的地址到addr
	@SP
	M=M-1 //SP--
	A=M //偏移到栈顶元素
	D=M //提取栈顶元素
	@addr
	A=M //跳转到argument[1]
	M=D //argument=D
	```
## 一般操作<a id="universal"></a>
- 一元操作(neg/not)<a id="sole"></a>
	```hack
	//not:非0值视为true，0视为false
	@SP
	A=M-1 //偏移至栈顶元素
	M=!M //对M逐位取非
	```
- 二元运算(add/sub/and/or)<a id="2op"></a>
	```hack
	//add
	@SP
	M=M-1
	A=M
	D=M //弹出第二个操作数b
	@SP
	A=M-1 //直接在操作数a的地址上操作
	M=D+M //将两数之和a+b压入栈顶
	```
- 二元判断(eq/gt/lt)<a id="2cp"></a>
	```hack
	//gt
	@SP
	M=M-1
	A=M
	D=M //弹出栈顶元素b
	@SP
	A=M-1 //获取操作数a
	D=M-D //D=b-a(lt改为D=D-M)
	@32767 //符号位为0其余为1
	A=A+1 //符号位为1其余为0
	D=D&A //取符号位
	D=D-A //若b-a<0，即a>b时D为0,否则为32768
	@SP
	A=M-1 //偏移到a的地址
	M=D //弹出a并压入结果
	```
## 实现技术<a id="trick"></a>
### 处理流程
1. 对传入文件进行整理，去除注释和空行，再将命令切分成段
2. 创建指向第一段命令的迭代器iter，根据命令类型选择对应工厂
3. 将iter传入工厂，创建命令实例，此时命令实例会自动获取需要的参数，并推进iter
4. 调用命令的编译方法得到汇编码，写入文件
### 工厂模式
1. 选择对应工厂:在VMFile中添加哈希表
   ```cpp
   class VMFile:public CommonFile{
	//忽略其他代码
	unordered_map<string,unique_ptr<CommandFactory>> factories_;//工厂集合
	VMFile(){
		//...
		factories_["push"]=make_unique<ConcreteFactory<PushCommand>>();//注册push命令工厂
	}
   };
   ```
2. [工厂类](/PartII/VMCompiler/include/Command/Factory.hpp)



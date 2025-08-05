# 实现VM码编译为汇编码
> - 假设输入均符合规范
> - 对于static内存段和标签，编译器行为与课程标准不同，生成的变量名和标签名会在开头多一个F，以防止由于vm文件以数字开头导致的错误
- [初始化与退出](#preset)
- [内存操作](#memory)
	- [push](#push)
	- [pop](#pop)
- [一般操作](#universal)
	- [not/neg](#sole)
	- [add/sub/and/or](#2op)
	- [eq/gt/lt](#2cp)
- [分支](#branch)
- [函数](#function)
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
- 在初始化结束后，要立即调用Sys.init
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
	M=M+1
	A=M-1 //前往栈
	M=D //压入栈中
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
	AM=M-1
	D=M
	@SP
	A=M-1
	M=M-D
	@XXX_TRUE //XXX是唯一前缀，由编译器生成
	D;JGT
	@SO
	A=M-1
	M=0 //假:结果为0
	@XXX_END
	0;JMP
	(XXX_TRUE)
	@SP
	A=M-1
	M=-1 //真:结果为-1
	(XXX_END)
	```
## 分支<a id="branch"></a>
- ```label LABEL``:声明标签
- ```goto LABEL``:跳跃到指定标签
- ```if-goto LABEL`:弹出栈顶元素，若其为真则跳跃到指定标签
## 函数<a id="function"></a>
- ```function name n```:声明一个名为name,需要n个局部变量的函数
	行为:声明一个函数全名标签，并在全局栈中准备n个变量作为local段
- ```call name n```:调用一个名为name的函数，并传入n个参数
	行为:根据n将参数指针ARG设置到栈上的正确位置，保存上下文(LCL/ARG/THIS/THAT)，同时正确设置栈顶指针，另外再设置函数返回后继续执行的地址，最后跳转到对应函数并设置上下文(LCL/ARG/THIS/THAT)
	```asm
	@foo$ret.1//返回地址标签格式:函数名$ret.调用call的次数
	D=A
	@SP
	M=M+1
	A=M-1
	M=D //将返回地址放入栈顶
	//省略push上下文的过程
	@i //i=5+nArgs
	D=A
	@SP
	D=M-D //得到调用者的ARG地址
	@ARG
	M=D //恢复ARG
	@SP
	D=M
	@LCL
	M=D //恢复LCL
	@foo //前往函数foo
	0;JMP
	(foo$ret.1)//返回点
	```
- ```return```:从函数返回值
	行为:将栈顶元素复制到argument[0]，并将栈顶指针SP设置为argument[1]，恢复调用者的上下文,跳跃到调用者
	```asm
	@LCL
	D=M
	@endFrame
	M=D //将调用者的上下文结尾保存在endFrame
	@5
	D=A
	@endFrame
	D=M-D //D=endFrame-5
	A=D 
	D=M//得到*(endFrame-5),即返回地址
	@retAddr
	M=D //存储返回地址
	@SP
	AM=M-1
	D=M //弹出栈顶元素(返回值)到D
	@ARG
	A=M
	M=D //将*ARG设置为函数返回值
	D=A //D设为ARG地址
	@SP
	M=D+1 //将栈顶指针设置为ARG+1
	@endFrame
	M=M-1
	D=M //更新endFrame的值为endFrame-1
	A=D
	D=M //得到*(endFrame-1),即调用者的THAT
	@THAT //恢复顺序与压入顺序相反
	M=D
	//省略其它上下文
	@retAddr//跳转到返回值地址
	0;JMP
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



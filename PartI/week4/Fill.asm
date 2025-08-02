// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.
@SCREEN
D=A
@addr
M=D //addr存储屏幕基址
@8191
D=A
@n
M=D //n存储屏幕映射区长度
(LOOP)
    @i
    M=0 //初始化绘制循环计数
    @KBD
    D=M //获取按键值

    @BLACK
    D;JNE //当按下任何按键则黑屏
    @WHITE
    D;JEQ //没按按键就白屏
    (BLACK)
        @i
        D=M
        @n
        D=M-D
        @LOOP
        D;JLE //当n-i<=0时，绘制结束

        //绘制流程：将每个单元设置为-1
        @addr
        D=M
        @i
        A=D+M //将A设置成addr+i
        M=-1 //将RAM[SCREEN+i]的每一位都设置为1

        @i
        M=M+1 //i++
        @BLACK
        0;JMP //返回循环顶
    (WHITE)
        @i
        D=M
        @n
        D=M-D
        @LOOP
        D;JLE
        @addr
        D=M
        @i
        A=D+M
        M=0
        @i
        M=M+1
        @WHITE
        0;JMP
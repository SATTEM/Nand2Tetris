// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.
@R2
M=0
@R1
D=M
@i
M=0
@n
M=D
(LOOP)
    @n
    D=M
    @i
    D=D-M
    @END
    D;JLE
    @R2
    D=M
    @R0
    D=D+M
    @R2
    M=D
    @i
    M=M+1
    @LOOP
    0;JMP
(END)
    0;JMP
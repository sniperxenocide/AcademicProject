.MODEL SMALL
.STACK 100h
.DATA
t0 dw ?
t1 dw ?
t2 dw ?
t3 dw ?
a dw ?, ?, ?
i dw ?
.CODE
main proc
mov ax,@DATA
mov ds,ax
mov ax, 1
mov bx, 2
mul bx
mov t0, ax
lea di, a
add di, t0
add di, t0
mov t1, [di]
mov ax, i
mov bx, t1
mul bx
mov t2, ax
mov ax, t2
lea di, a
add di, 1
add di, 1
mov [di], ax
mov ax, i
cmp ax, 2
jl L0
mov t3, 0
jmp L1
L0:
mov t3, 1
L1:
mov ax, t3
cmp ax, 1
jne L2
mov ax, 5
lea di, a
add di, 2
add di, 2
mov [di], ax
L2:
mov ax, 7
lea di, a
add di, 3
add di, 3
mov [di], ax


PRINTLN PROC
PUSH AXvPUSH BX
PUSH CX
PUSH DX
OR AX,AX
JGE @END_IF1
PUSH AX
MOV DL,'-'
MOV AH,2
INT 21H
POP AX
NEG AX
@END_IF1:
XOR CX,CX
MOV BX,10D
@REPEAT1:
XOR DX,DX
DIV BX
PUSH DX
INC CX
OR AX,AX
JNE @REPEAT1
MOV AH,2
@PRINT_LOOP:
POP DX
OR DL,30H
INT 21H
LOOP @PRINT_LOOP
POP DX
POP CX
POP BX
POP AX
RET
PRINTLN ENDP
END MAIN

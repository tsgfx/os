BITS 16 ;指定汇编代码为16位
start:
    mov ah, 0x0e ;使用视频模式
    mov al, 'H' ;要显示的字符
    int 0x10 ;中断,使用BIOS视频服务
hang:
    jmp hang ;死循环
times 510-($-start) db 0 ;填充至510字节
dw 0xAA55 ;最后两个字节存放MBR
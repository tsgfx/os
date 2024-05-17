- 使用gas
编译：
as -o hello.o hello.s
链接：
ld -s -o hello hello.o
使用gcc
gcc -o hello hello.s

- 使用nasm
编译：
nasm -f elf64 hello.asm
链接：
ld -s -o hello hello.o
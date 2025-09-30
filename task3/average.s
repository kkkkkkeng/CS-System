    .section .rodata
lpfmt:
    .string "%s %s %d %d\n\0"
lpfmt_string:
    .string "%s  \0"
lpfmt_num:
    .string "%d  \0"

    .text
    .globl display
    .globl average
    .type display, @function
    .type average,@function

# void display(student* sptr, int num)
# 参数传递规则 (cdecl, 32位 Linux):
#   [esp+4] = sptr
#   [esp+8] = num
display:
    pushl   %ebp
    movl    %esp, %ebp          # 保存ebp, 将ebp设为当前esp

    pusha

    movl    8(%ebp), %ebx        # sptr (student* s)

    # printf("%s  ", sname)
    pushl   %ebx                 # 参数: s->sname
    pushl   $lpfmt_string
    call    printf
    addl    $8, %esp

    # printf("%s  ", sid)
    leal    8(%ebx), %eax        # sid 偏移 8
    pushl   %eax
    pushl   $lpfmt_string
    call    printf
    addl    $8, %esp

    # printf("%d  ", scores[0])
    movzwl  20(%ebx), %eax       # scores[0] 偏移 20
    pushl   %eax
    pushl   $lpfmt_num
    call    printf
    addl    $8, %esp

    # printf("%d  ", scores[2])
    movzwl  24(%ebx), %eax       # scores[2] 偏移 24
    pushl   %eax
    pushl   $lpfmt_num
    call    printf
    addl    $8, %esp
    
    popa

    movl    %ebp, %esp
    popl    %ebp
    ret

average:
#void average(student* s,int num)
#[esp+4] s
#[esp+8] num
    pushl %ebp
    movl %esp,%ebp
    pusha
    movl 0x8(%ebp),%esi
    add $0x14,%esi
    
outer:
    movl 0xc(%ebp),%ecx
    xor %eax,%eax
    movl $0x8,%edx
inner:
    movswl (%esi),%ebx
    add %ebx,%eax
    add $0x2,%esi
    dec %edx
    jnz inner
    movb $0x8,%dl
    idivb %dl
    movsbw %al,%dx
    movw %dx,(%esi)
    add $0x16,%esi
    dec %ecx
    jnz outer

    popa

    movl %ebp,%esp
    pop %ebp
    ret
    
    


    
    .section .note.GNU-stack,"",@progbits

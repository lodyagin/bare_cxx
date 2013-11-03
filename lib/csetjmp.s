// -*-coding: mule-utf-8-unix; fill-column: 58 -*-
/** 
 * @file
 *
 * This file is a part of Bare C++ library. Bare C++ library is a standard
 * library specially designed for systems without memory protection like
 * exokernel operating systems.
 *
 * @author Sergei Lodyagin <serg@kogorta.dp.ua>
 * @copyright (C) 2013 Cohors LLC
 *
 */

        .text        
//========================================================
// int setjmp(jmp_buf)
//
        
.globl setjmp
setjmp:
        movq   %rsp, (%rdi)
        movq   %rbp, 8(%rdi)
        movq   %rbx, 16(%rdi)
        movq   %r12, 24(%rdi)
        movq   %r13, 32(%rdi)
        movq   %r14, 40(%rdi)
        movq   %r15, 48(%rdi)
        
        // the return address 
        movq   (%rsp), %rax
        movq   %rax, 56(%rdi)   

        xorq   %rax, %rax
        ret

//========================================================
// int longjmp(jmp_buf, int status)
//

.globl longjmp
longjmp:
        movq   (%rdi), %rsp
        movq   8(%rdi), %rbp
        movq   16(%rdi), %rbx
        movq   24(%rdi), %r12
        movq   32(%rdi), %r13
        movq   40(%rdi), %r14
        movq   48(%rdi), %r15

        // overwrite some stack value
        movq   56(%rdi), %rax
        movq   %rax, (%rsp)
        
        movq   %rsi, %rax
        ret
    
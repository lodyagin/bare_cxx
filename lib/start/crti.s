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

.section .init

.global _init
_init:
        push %rbp
        mov  %rsp, %rbp

.section .fini

.global _fini
_fini:
        push %rbp
        mov  %rsp, %rbp


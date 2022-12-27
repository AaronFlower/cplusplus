	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 12, 1
	.globl	__Z13add_unrollingv             ## -- Begin function _Z13add_unrollingv
	.p2align	4, 0x90
__Z13add_unrollingv:                    ## @_Z13add_unrollingv
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	.p2align	4, 0x90
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	_a(%rip), %edx
	imull	%ecx, %edx
	leal	1(%rcx), %esi
	imull	_a(%rip), %esi
	addl	%eax, %edx
	leal	2(%rcx), %edi
	imull	_a(%rip), %edi
	addl	%edx, %esi
	leal	3(%rcx), %eax
	imull	_a(%rip), %eax
	addl	%esi, %edi
	addl	%edi, %eax
	addl	$4, %ecx
	cmpl	$134217728, %ecx                ## imm = 0x8000000
	jne	LBB0_1
## %bb.2:
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__Z8add_loopv                   ## -- Begin function _Z8add_loopv
	.p2align	4, 0x90
__Z8add_loopv:                          ## @_Z8add_loopv
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	.p2align	4, 0x90
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	_b(%rip), %edx
	imull	%ecx, %edx
	leal	1(%rcx), %esi
	imull	_b(%rip), %esi
	addl	%eax, %edx
	leal	2(%rcx), %edi
	imull	_b(%rip), %edi
	addl	%edx, %esi
	leal	3(%rcx), %eax
	imull	_b(%rip), %eax
	addl	%esi, %edi
	addl	%edi, %eax
	addl	$4, %ecx
	cmpl	$134217728, %ecx                ## imm = 0x8000000
	jne	LBB1_1
## %bb.2:
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__literal4,4byte_literals
	.p2align	2                               ## -- Begin function main
LCPI2_0:
	.long	0x49742400                      ## float 1.0E+6
LCPI2_1:
	.long	0x447a0000                      ## float 1000
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%rbx
	pushq	%rax
	.cfi_offset %rbx, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	xorl	%r15d, %r15d
	callq	_clock
	movq	%rax, %r14
	xorl	%ebx, %ebx
	.p2align	4, 0x90
LBB2_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	_b(%rip), %eax
	imull	%r15d, %eax
	leal	1(%r15), %ecx
	imull	_b(%rip), %ecx
	addl	%ebx, %eax
	leal	2(%r15), %edx
	imull	_b(%rip), %edx
	addl	%eax, %ecx
	leal	3(%r15), %ebx
	imull	_b(%rip), %ebx
	addl	%ecx, %edx
	addl	%edx, %ebx
	addl	$4, %r15d
	cmpl	$134217728, %r15d               ## imm = 0x8000000
	jne	LBB2_1
## %bb.2:
	callq	_clock
	subq	%r14, %rax
	js	LBB2_3
## %bb.4:
	cvtsi2ss	%rax, %xmm0
	jmp	LBB2_5
LBB2_3:
	movq	%rax, %rcx
	shrq	%rcx
	andl	$1, %eax
	orq	%rcx, %rax
	cvtsi2ss	%rax, %xmm0
	addss	%xmm0, %xmm0
LBB2_5:
	divss	LCPI2_0(%rip), %xmm0
	mulss	LCPI2_1(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	leaq	L_.str(%rip), %rdi
	movl	%ebx, %esi
	movb	$1, %al
	callq	_printf
	xorl	%r15d, %r15d
	callq	_clock
	movq	%rax, %r14
	xorl	%ebx, %ebx
	.p2align	4, 0x90
LBB2_6:                                 ## =>This Inner Loop Header: Depth=1
	movl	_a(%rip), %eax
	imull	%r15d, %eax
	leal	1(%r15), %ecx
	imull	_a(%rip), %ecx
	addl	%ebx, %eax
	leal	2(%r15), %edx
	imull	_a(%rip), %edx
	addl	%eax, %ecx
	leal	3(%r15), %ebx
	imull	_a(%rip), %ebx
	addl	%ecx, %edx
	addl	%edx, %ebx
	addl	$4, %r15d
	cmpl	$134217728, %r15d               ## imm = 0x8000000
	jne	LBB2_6
## %bb.7:
	callq	_clock
	subq	%r14, %rax
	js	LBB2_8
## %bb.9:
	xorps	%xmm0, %xmm0
	cvtsi2ss	%rax, %xmm0
	jmp	LBB2_10
LBB2_8:
	movq	%rax, %rcx
	shrq	%rcx
	andl	$1, %eax
	orq	%rcx, %rax
	xorps	%xmm0, %xmm0
	cvtsi2ss	%rax, %xmm0
	addss	%xmm0, %xmm0
LBB2_10:
	divss	LCPI2_0(%rip), %xmm0
	mulss	LCPI2_1(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	leaq	L_.str.1(%rip), %rdi
	movl	%ebx, %esi
	movb	$1, %al
	callq	_printf
	xorl	%eax, %eax
	addq	$8, %rsp
	popq	%rbx
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__DATA,__data
	.globl	_a                              ## @a
	.p2align	2
_a:
	.long	2                               ## 0x2

	.globl	_b                              ## @b
	.p2align	2
_b:
	.long	2                               ## 0x2

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"     add_loop = %d, %.4fms\n"

L_.str.1:                               ## @.str.1
	.asciz	"add_unrolling = %d, %.4fms\n"

.subsections_via_symbols

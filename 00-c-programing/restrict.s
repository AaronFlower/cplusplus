	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 12, 1
	.intel_syntax noprefix
	.globl	_foo                            ## -- Begin function foo
	.p2align	4, 0x90
_foo:                                   ## @foo
	.cfi_startproc
## %bb.0:
	mov	dword ptr [rdi], 5
	mov	dword ptr [rsi], 6
	mov	eax, dword ptr [rdi]
	add	eax, 6
	ret
	.cfi_endproc
                                        ## -- End function
	.globl	_rfoo                           ## -- Begin function rfoo
	.p2align	4, 0x90
_rfoo:                                  ## @rfoo
	.cfi_startproc
## %bb.0:
	mov	dword ptr [rdi], 5
	mov	dword ptr [rsi], 6
	mov	eax, 11
	ret
	.cfi_endproc
                                        ## -- End function
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	push	r14
	.cfi_def_cfa_offset 16
	push	rbx
	.cfi_def_cfa_offset 24
	push	rax
	.cfi_def_cfa_offset 32
	.cfi_offset rbx, -24
	.cfi_offset r14, -16
	lea	r14, [rip + L_.str]
	mov	rdi, r14
	mov	esi, 11
	xor	eax, eax
	call	_printf
	lea	rbx, [rip + L_.str.1]
	mov	rdi, rbx
	mov	esi, 11
	xor	eax, eax
	call	_printf
	mov	rdi, r14
	mov	esi, 12
	xor	eax, eax
	call	_printf
	mov	rdi, rbx
	mov	esi, 11
	xor	eax, eax
	call	_printf
	xor	eax, eax
	add	rsp, 8
	pop	rbx
	pop	r14
	ret
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	" foo = %d\n"

L_.str.1:                               ## @.str.1
	.asciz	"rfoo = %d\n"

.subsections_via_symbols

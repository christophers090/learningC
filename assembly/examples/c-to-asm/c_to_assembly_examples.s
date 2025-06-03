	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0	sdk_version 14, 0
	.globl	_simple_assignment              ; -- Begin function simple_assignment
	.p2align	2
_simple_assignment:                     ; @simple_assignment
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	mov	w8, #10
	str	w8, [sp, #12]
	mov	w8, #20
	str	w8, [sp, #8]
	ldr	w8, [sp, #12]
	ldr	w9, [sp, #8]
	add	w8, w8, w9
	str	w8, [sp, #4]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_simple_if                      ; -- Begin function simple_if
	.p2align	2
_simple_if:                             ; @simple_if
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	w0, [x29, #-4]
	ldur	w8, [x29, #-4]
	subs	w8, w8, #10
	cset	w8, le
	tbnz	w8, #0, LBB1_2
	b	LBB1_1
LBB1_1:
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	b	LBB1_3
LBB1_2:
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	b	LBB1_3
LBB1_3:
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_simple_loop                    ; -- Begin function simple_loop
	.p2align	2
_simple_loop:                           ; @simple_loop
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	wzr, [sp, #12]
	str	wzr, [sp, #8]
	b	LBB2_1
LBB2_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #8]
	subs	w8, w8, #5
	cset	w8, ge
	tbnz	w8, #0, LBB2_4
	b	LBB2_2
LBB2_2:                                 ;   in Loop: Header=BB2_1 Depth=1
	ldr	w9, [sp, #8]
	ldr	w8, [sp, #12]
	add	w8, w8, w9
	str	w8, [sp, #12]
	b	LBB2_3
LBB2_3:                                 ;   in Loop: Header=BB2_1 Depth=1
	ldr	w8, [sp, #8]
	add	w8, w8, #1
	str	w8, [sp, #8]
	b	LBB2_1
LBB2_4:
	ldr	w0, [sp, #12]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_add_numbers                    ; -- Begin function add_numbers
	.p2align	2
_add_numbers:                           ; @add_numbers
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	w0, [sp, #12]
	str	w1, [sp, #8]
	ldr	w8, [sp, #12]
	ldr	w9, [sp, #8]
	add	w0, w8, w9
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_call_function                  ; -- Begin function call_function
	.p2align	2
_call_function:                         ; @call_function
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	w0, #5
	mov	w1, #3
	bl	_add_numbers
	stur	w0, [x29, #-4]
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_array_example                  ; -- Begin function array_example
	.p2align	2
_array_example:                         ; @array_example
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	add	x29, sp, #48
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	stur	x8, [x29, #-8]
	adrp	x8, l___const.array_example.arr@PAGE
	add	x8, x8, l___const.array_example.arr@PAGEOFF
	ldr	q0, [x8]
	str	q0, [sp, #16]
	ldr	w8, [x8, #16]
	str	w8, [sp, #32]
	ldr	w8, [sp, #24]
	str	w8, [sp, #12]
	mov	w8, #10
	str	w8, [sp, #20]
	ldur	x9, [x29, #-8]
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	subs	x8, x8, x9
	cset	w8, eq
	tbnz	w8, #0, LBB5_2
	b	LBB5_1
LBB5_1:
	bl	___stack_chk_fail
LBB5_2:
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	add	sp, sp, #64
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_pointer_example                ; -- Begin function pointer_example
	.p2align	2
_pointer_example:                       ; @pointer_example
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	add	x8, sp, #28
	mov	w9, #42
	str	w9, [sp, #28]
	str	x8, [sp, #16]
	ldr	x8, [sp, #16]
	ldr	w8, [x8]
	str	w8, [sp, #12]
	ldr	x9, [sp, #16]
	mov	w8, #100
	str	w8, [x9]
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_bitwise_example                ; -- Begin function bitwise_example
	.p2align	2
_bitwise_example:                       ; @bitwise_example
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	mov	w8, #255
	str	w8, [sp, #28]
	mov	w8, #15
	str	w8, [sp, #24]
	ldr	w8, [sp, #28]
	ldr	w9, [sp, #24]
	and	w8, w8, w9
	str	w8, [sp, #20]
	ldr	w8, [sp, #28]
	ldr	w9, [sp, #24]
	orr	w8, w8, w9
	str	w8, [sp, #16]
	ldr	w8, [sp, #28]
	ldr	w9, [sp, #24]
	eor	w8, w8, w9
	str	w8, [sp, #12]
	ldr	w8, [sp, #28]
	lsl	w8, w8, #2
	str	w8, [sp, #8]
	ldr	w8, [sp, #28]
	asr	w8, w8, #1
	str	w8, [sp, #4]
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	w8, #0
	stur	w8, [x29, #-12]                 ; 4-byte Folded Spill
	stur	wzr, [x29, #-4]
	adrp	x0, l_.str.2@PAGE
	add	x0, x0, l_.str.2@PAGEOFF
	bl	_printf
	bl	_simple_assignment
	mov	w0, #15
	bl	_simple_if
	mov	w0, #5
	bl	_simple_if
	bl	_simple_loop
	stur	w0, [x29, #-8]
	ldur	w9, [x29, #-8]
                                        ; implicit-def: $x8
	mov	x8, x9
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_.str.3@PAGE
	add	x0, x0, l_.str.3@PAGEOFF
	bl	_printf
	bl	_call_function
	bl	_array_example
	bl	_pointer_example
	bl	_bitwise_example
	ldur	w0, [x29, #-12]                 ; 4-byte Folded Reload
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Big number\n"

l_.str.1:                               ; @.str.1
	.asciz	"Small number\n"

	.section	__TEXT,__const
	.p2align	2, 0x0                          ; @__const.array_example.arr
l___const.array_example.arr:
	.long	1                               ; 0x1
	.long	2                               ; 0x2
	.long	3                               ; 0x3
	.long	4                               ; 0x4
	.long	5                               ; 0x5

	.section	__TEXT,__cstring,cstring_literals
l_.str.2:                               ; @.str.2
	.asciz	"C to Assembly Examples\n"

l_.str.3:                               ; @.str.3
	.asciz	"Loop result: %d\n"

.subsections_via_symbols

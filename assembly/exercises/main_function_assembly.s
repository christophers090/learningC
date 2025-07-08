# Assembly output from: objdump -d learn_with_objdump | grep -A 30 "<_main>:"
# Original C code:
# int main() {
#     int x = 1337;
#     while(x--) {
#         printf("ayo\n");
#     }
#     return 0;
# }

0000000100003f3c <_main>:
100003f3c: d10083ff    	sub	sp, sp, #32
100003f40: a9017bfd    	stp	x29, x30, [sp, #16]
100003f44: 910043fd    	add	x29, sp, #16
100003f48: b81fc3bf    	stur	wzr, [x29, #-4]
100003f4c: 5280a728    	mov	w8, #1337
100003f50: b9000be8    	str	w8, [sp, #8]
100003f54: 14000001    	b	0x100003f58 <_main+0x1c>
100003f58: b9400be8    	ldr	w8, [sp, #8]
100003f5c: 71000509    	subs	w9, w8, #1
100003f60: b9000be9    	str	w9, [sp, #8]
100003f64: 71000108    	subs	w8, w8, #0
100003f68: 1a9f17e8    	cset	w8, eq
100003f6c: 370000c8    	tbnz	w8, #0, 0x100003f84 <_main+0x48>
100003f70: 14000001    	b	0x100003f74 <_main+0x38>
100003f74: 90000000    	adrp	x0, 0x100003000 <_main+0x38>
100003f78: 913e8000    	add	x0, x0, #4000
100003f7c: 94000006    	bl	0x100003f94 <_printf+0x100003f94>
100003f80: 17fffff6    	b	0x100003f58 <_main+0x1c>
100003f84: 52800000    	mov	w0, #0
100003f88: a9417bfd    	ldp	x29, x30, [sp, #16]
100003f8c: 910083ff    	add	sp, sp, #32
100003f90: d65f03c0    	ret

# Disassembly of section __TEXT,__stubs:

0000000100003f94 <__stubs>:
100003f94: b0000010    	adrp	x16, 0x100004000 <__stubs+0x4>
100003f98: f9400210    	ldr	x16, [x16]
100003f9c: d61f0200    	br	x16 

# big function
0000000100003ef4 <_main>:
100003ef4: d10583ff    	sub	sp, sp, #352
100003ef8: a9146ffc    	stp	x28, x27, [sp, #320]
100003efc: a9157bfd    	stp	x29, x30, [sp, #336]
100003f00: 910543fd    	add	x29, sp, #336
100003f04: b0000008    	adrp	x8, 0x100004000 <_main+0x14>
100003f08: f9400508    	ldr	x8, [x8, #8]
100003f0c: f9400108    	ldr	x8, [x8]
100003f10: f81e83a8    	stur	x8, [x29, #-24]
100003f14: b9002fff    	str	wzr, [sp, #44]
100003f18: 528001a8    	mov	w8, #13
100003f1c: b9000fe8    	str	w8, [sp, #12]
100003f20: 14000001    	b	0x100003f24 <_main+0x30>
100003f24: b9400fe8    	ldr	w8, [sp, #12]
100003f28: 71000509    	subs	w9, w8, #1
100003f2c: b9000fe9    	str	w9, [sp, #12]
100003f30: 71000108    	subs	w8, w8, #0
100003f34: 1a9f17e8    	cset	w8, eq
100003f38: 370000c8    	tbnz	w8, #0, 0x100003f50 <_main+0x5c>
100003f3c: 14000001    	b	0x100003f40 <_main+0x4c>
100003f40: 90000000    	adrp	x0, 0x100003000 <_main+0x4c>
100003f44: 913e8000    	add	x0, x0, #4000
100003f48: 94000013    	bl	0x100003f94 <_printf+0x100003f94>
100003f4c: 17fffff6    	b	0x100003f24 <_main+0x30>
100003f50: f85e83a9    	ldur	x9, [x29, #-24]
100003f54: b0000008    	adrp	x8, 0x100004000 <_main+0x64>
100003f58: f9400508    	ldr	x8, [x8, #8]
100003f5c: f9400108    	ldr	x8, [x8]
100003f60: eb090108    	subs	x8, x8, x9
100003f64: 1a9f17e8    	cset	w8, eq
100003f68: 37000068    	tbnz	w8, #0, 0x100003f74 <_main+0x80>
100003f6c: 14000001    	b	0x100003f70 <_main+0x7c>
100003f70: 94000006    	bl	0x100003f88 <_printf+0x100003f88>
100003f74: 52800000    	mov	w0, #0
100003f78: a9557bfd    	ldp	x29, x30, [sp, #336]
100003f7c: a9546ffc    	ldp	x28, x27, [sp, #320]
100003f80: 910583ff    	add	sp, sp, #352
100003f84: d65f03c0    	ret

Disassembly of section __TEXT,__stubs:

0000000100003f88 <__stubs>:
100003f88: b0000010    	adrp	x16, 0x100004000 <__stubs+0x4>
100003f8c: f9400210    	ldr	x16, [x16]
100003f90: d61f0200    	br	x16
100003f94: b0000010    	adrp	x16, 0x100004000 <__stubs+0x10>
100003f98: f9400a10    	ldr	x16, [x16, #16]
100003f9c: d61f0200    	br	x16

# Added assembly for if_executable's main function:
# Original C code for if.c:
# int main() {
#     int a = 10;
#     int b = 20;
#     int result = 0;
#
#     if (a < b) {
#         result = 1; // Condition is true
#     } else {
#         result = 2; // Condition is false
#     }
#     return result;
# }

0000000100003f50 <_main>:
100003f50: d10043ff     sub     sp, sp, #16
100003f54: b9000fff     str     wzr, [sp, #12]
100003f58: 52800148     mov     w8, #10
100003f5c: b9000be8     str     w8, [sp, #8]
100003f60: 52800288     mov     w8, #20
100003f64: b90007e8     str     w8, [sp, #4]
100003f68: b90003ff     str     wzr, [sp]
100003f6c: b9400be8     ldr     w8, [sp, #8]
100003f70: b94007e9     ldr     w9, [sp, #4]
100003f74: 6b090108     subs    w8, w8, w9
100003f78: 1a9fb7e8     cset    w8, ge
100003f7c: 370000a8     tbnz    w8, #0, 0x100003f90 <_main+0x40>
100003f80: 14000001     b       0x100003f84 <_main+0x34>
100003f84: 52800028     mov     w8, #1
100003f88: b90003e8     str     w8, [sp]
100003f8c: 14000004     b       0x100003f9c <_main+0x4c>
100003f90: 52800048     mov     w8, #2
100003f94: b90003e8     str     w8, [sp]
100003f98: 14000001     b       0x100003f9c <_main+0x4c>
100003f9c: b94003e0     ldr     w0, [sp]
100003fa0: 910043ff     add     sp, sp, #16
100003fa4: d65f03c0     ret

# Added assembly for for_executable's main function:
# Original C code for for.c:
# int main() {
#     int sum = 0;
#     int i;
#
#     for (i = 0; i < 5; i++) {
#         sum = sum + i;
#     }
#
#     return sum;
# }

0000000100003f50 <_main>:
100003f50: d10043ff     sub     sp, sp, #16
100003f54: b9000fff     str     wzr, [sp, #12]
100003f58: b9000bff     str     wzr, [sp, #8]
100003f5c: b90007ff     str     wzr, [sp, #4]
100003f60: 14000001     b       0x100003f64 <_main+0x14>
100003f64: b94007e8     ldr     w8, [sp, #4]
100003f68: 71001508     subs    w8, w8, #5
100003f6c: 1a9fb7e8     cset    w8, ge
100003f70: 37000168     tbnz    w8, #0, 0x100003f9c <_main+0x4c>
100003f74: 14000001     b       0x100003f78 <_main+0x28>
100003f78: b9400be8     ldr     w8, [sp, #8]
100003f7c: b94007e9     ldr     w9, [sp, #4]
100003f80: 0b090108     add     w8, w8, w10
100003f84: b9000be8     str     w8, [sp, #8]
100003f88: 14000001     b       0x100003f8c <_main+0x3c>
100003f8c: b94007e8     ldr     w8, [sp, #4]
100003f90: 11000508     add     w8, w8, #1
100003f94: b90007e8     str     w8, [sp, #4]
100003f98: 17fffff3     b       0x100003f64 <_main+0x14>
100003f9c: b9400be0     ldr     w0, [sp, #8]
100003fa0: 910043ff     add     sp, sp, #16
100004fa4: d65f03c0     
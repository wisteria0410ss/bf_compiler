.intel_syntax noprefix
.global _start

.data
buf:
	.zero 65536

.text
read:
	lea  rsi, [rbx]
	xor  rax, rax
	mov  rdi, 1
	mov  rdx, rdi
	syscall
	retq
write:
	lea  rsi, [rbx]
	mov  rdx, 1
	mov  rax, rdx
	mov  rdi, rdx
	syscall
	retq
_start:
	lea  rbx, [buf]
	inc  rbx
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
.L0:
	cmp  byte ptr [rbx], 0
	je   .L0_END
	dec  rbx
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  rbx
	dec  byte ptr [rbx]
	jmp  .L0
.L0_END:
	dec  rbx
	call write
	inc  rbx
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
.L1:
	cmp  byte ptr [rbx], 0
	je   .L1_END
	dec  rbx
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  rbx
	dec  byte ptr [rbx]
	jmp  .L1
.L1_END:
	dec  rbx
	inc  byte ptr [rbx]
	call write
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	call write
	call write
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	call write
.L2:
	cmp  byte ptr [rbx], 0
	je   .L2_END
	dec  byte ptr [rbx]
	jmp  .L2
.L2_END:
	inc  rbx
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
.L3:
	cmp  byte ptr [rbx], 0
	je   .L3_END
	dec  rbx
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  rbx
	dec  byte ptr [rbx]
	jmp  .L3
.L3_END:
	dec  rbx
	call write
	inc  rbx
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
.L4:
	cmp  byte ptr [rbx], 0
	je   .L4_END
	dec  rbx
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  rbx
	dec  byte ptr [rbx]
	jmp  .L4
.L4_END:
	dec  rbx
	call write
	inc  rbx
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
.L5:
	cmp  byte ptr [rbx], 0
	je   .L5_END
	dec  rbx
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  rbx
	dec  byte ptr [rbx]
	jmp  .L5
.L5_END:
	dec  rbx
	call write
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	call write
	dec  byte ptr [rbx]
	dec  byte ptr [rbx]
	dec  byte ptr [rbx]
	dec  byte ptr [rbx]
	dec  byte ptr [rbx]
	dec  byte ptr [rbx]
	call write
	dec  byte ptr [rbx]
	dec  byte ptr [rbx]
	dec  byte ptr [rbx]
	dec  byte ptr [rbx]
	dec  byte ptr [rbx]
	dec  byte ptr [rbx]
	dec  byte ptr [rbx]
	dec  byte ptr [rbx]
	call write
.L6:
	cmp  byte ptr [rbx], 0
	je   .L6_END
	dec  byte ptr [rbx]
	jmp  .L6
.L6_END:
	inc  rbx
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
.L7:
	cmp  byte ptr [rbx], 0
	je   .L7_END
	dec  rbx
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  rbx
	dec  byte ptr [rbx]
	jmp  .L7
.L7_END:
	dec  rbx
	inc  byte ptr [rbx]
	call write
.L8:
	cmp  byte ptr [rbx], 0
	je   .L8_END
	dec  byte ptr [rbx]
	jmp  .L8
.L8_END:
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	inc  byte ptr [rbx]
	call write
	mov  rax, 0x3c
	xor  rdi, rdi
	syscall

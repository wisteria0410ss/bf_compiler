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
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
.L0:
	cmp  dword ptr [rbx], 0
	je   .L0_END
	dec  rbx
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  rbx
	dec  dword ptr [rbx]
	jmp  .L0
.L0_END:
	dec  rbx
	call write
	inc  rbx
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
.L1:
	cmp  dword ptr [rbx], 0
	je   .L1_END
	dec  rbx
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  rbx
	dec  dword ptr [rbx]
	jmp  .L1
.L1_END:
	dec  rbx
	inc  dword ptr [rbx]
	call write
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	call write
	call write
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	call write
.L2:
	cmp  dword ptr [rbx], 0
	je   .L2_END
	dec  dword ptr [rbx]
	jmp  .L2
.L2_END:
	inc  rbx
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
.L3:
	cmp  dword ptr [rbx], 0
	je   .L3_END
	dec  rbx
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  rbx
	dec  dword ptr [rbx]
	jmp  .L3
.L3_END:
	dec  rbx
	call write
	inc  rbx
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
.L4:
	cmp  dword ptr [rbx], 0
	je   .L4_END
	dec  rbx
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  rbx
	dec  dword ptr [rbx]
	jmp  .L4
.L4_END:
	dec  rbx
	call write
	inc  rbx
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
.L5:
	cmp  dword ptr [rbx], 0
	je   .L5_END
	dec  rbx
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  rbx
	dec  dword ptr [rbx]
	jmp  .L5
.L5_END:
	dec  rbx
	call write
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	call write
	dec  dword ptr [rbx]
	dec  dword ptr [rbx]
	dec  dword ptr [rbx]
	dec  dword ptr [rbx]
	dec  dword ptr [rbx]
	dec  dword ptr [rbx]
	call write
	dec  dword ptr [rbx]
	dec  dword ptr [rbx]
	dec  dword ptr [rbx]
	dec  dword ptr [rbx]
	dec  dword ptr [rbx]
	dec  dword ptr [rbx]
	dec  dword ptr [rbx]
	dec  dword ptr [rbx]
	call write
.L6:
	cmp  dword ptr [rbx], 0
	je   .L6_END
	dec  dword ptr [rbx]
	jmp  .L6
.L6_END:
	inc  rbx
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
.L7:
	cmp  dword ptr [rbx], 0
	je   .L7_END
	dec  rbx
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  rbx
	dec  dword ptr [rbx]
	jmp  .L7
.L7_END:
	dec  rbx
	inc  dword ptr [rbx]
	call write
.L8:
	cmp  dword ptr [rbx], 0
	je   .L8_END
	dec  dword ptr [rbx]
	jmp  .L8
.L8_END:
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	inc  dword ptr [rbx]
	call write
	mov  rax, 0x3c
	xor  rdi, 0x00
	syscall

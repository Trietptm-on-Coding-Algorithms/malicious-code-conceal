		BITS	32
		global	_start
		section .text

_start:		mov	esi, _virus
		mov	edi, virus
		mov	ecx, code_size
		cld
		rep	movsb
		jmp	virus

_virus:		call	.L0
.L0:		pop	ebp
		sub	ebp, .L0
		align	1024
		mov	eax, [ebp + var]
		int	3
var		dd	0x55aa55aa
code_size	equ	$ - _virus

		section .bss
virus:		resb	4096

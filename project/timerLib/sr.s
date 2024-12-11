.arch msp430g2553
.p2align 1,0
.text

;; Routines to manipulate special registers
.global set_sr
set_sr: nop
	mov r12, r2
	nop
	ret

.global get_sr
get_sr: mov r2, r12
	ret

.global or_sr
or_sr: nop
	bis r12, r2
	nop
	ret

.global and_sr
and_sr: nop
	and r12, r2
	nop
	ret

;; New functionality: Pulse fade effect for green LED
.global pulse_fade_green_led
pulse_fade_green_led:
	mov #0, r15
loop:
	cmp #255, r15
	jeq decrease
	inc r15
	mov r15, &P1OUT
	nop
	jmp loop

decrease:
	cmp #0, r15
	jeq exit
	dec r15
	mov r15, &P1OUT
	nop
	jmp decrease
exit:
	nop
	ret

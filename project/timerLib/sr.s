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

;; New functionality: Toggle LED brightness level
.global toggle_led_brightness
toggle_led_brightness:
	nop
	cmp #0, r12
	jeq low_brightness
	high_brightness:
	mov #0xFF, &P1OUT
	jmp exit
	low_brightness:
	mov #0x55, &P1OUT
	exit:
	nop
	ret

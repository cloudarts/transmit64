.pc = $0801 "Basic Upstart"
:BasicUpstart(start) 
.pc = $0810 "Program"

.import source "sub_mul.asm"

start:	lda #3
		sta sub_mul_int16_val1
		lda #100
		sta sub_mul_int16_val2
		jsr sub_mul_int16
end:	rts
.pc = $0801 "Basic Upstart"
:BasicUpstart(start) 
.pc = $0810 "Program"

.import source "sub_input.asm"

start:	jsr sub_input
		rts
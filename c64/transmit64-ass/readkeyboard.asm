.pc = $0801 "Basic Upstart"
:BasicUpstart(start) 
.pc = $0810 "Program"

.import source "sub_input.asm"
.import source "sub_print.asm"

start:	jsr sub_input        // get input
        lda #<sub_input_buff  // write address of input to zero page
        sta $FB
        lda #>sub_input_buff
        sta $FC
        ldx #2              // set output colum
        ldy #10             // set output row
        jsr sub_print       // print        
		rts
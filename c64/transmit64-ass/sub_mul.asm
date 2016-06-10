.importonce

//  multiply short(8) routine
//  in:
//      memory (byte) sub_mul_short_val1: val1
//      memory (byte) sub_mul_short_val2: val2
//  out: 
//      A: result
//  changes: A, X

sub_mul_short:      lda #0                  // write 0 to A
                    ldx sub_mul_short_val2  // use X as counter (val2)
sub_mul_short_loop: cpx	#0                  // begin of loop
                    beq sub_mul_short_end   // if X == 0, then exit
                    clc                     // clear carry flag
                    adc sub_mul_short_val1  // add val1 to A
                    dex                     // decrement X
                    jmp sub_mul_short_loop

sub_mul_short_end:  rts                      // return from subroutine
sub_mul_short_val1: .byte 0                 // memory for operand variable
sub_mul_short_val2: .byte 0                 // memory for operand variable


//--------------------------------------------------------------------------
//  multiply int(16) routine: 8bit * 8bit = 16bit
//  in:
//      memory (byte) sub_mul_int16_val1: val1
//      memory (byte) sub_mul_int16_val2: val2
//  out: 
//      memory sub_mul_int16_res1: result lower byte
//      memory sub_mul_int16_res2: result upper byte
//  changes: A, X

sub_mul_int16:      lda #0                      // write 0 to A
                    sta sub_mul_int16_res1      // clear result low
                    sta sub_mul_int16_res2      // clear result high
                    ldx sub_mul_int16_val2      // use X as counter (val2)
sub_mul_int16_loop: cpx #0                      // begin of loop
                    beq sub_mul_int16_end       // if X == 0, then exit
                    lda sub_mul_int16_res1      // load result low
                    clc                         // clear carry flag
                    adc sub_mul_int16_val1      // add val1 to A
                    sta sub_mul_int16_res1      // store result low
                    lda sub_mul_int16_res2      // load result high
                    adc #0                      // add carry to result high
                    sta sub_mul_int16_res2      // store result high
                    dex                         // decrement X
                    jmp sub_mul_int16_loop

sub_mul_int16_end:  rts                         // return from subroutine
sub_mul_int16_val1: .byte 0                     // memory for operand variable
sub_mul_int16_val2: .byte 0                     // memory for operand variable
sub_mul_int16_res1: .byte 0                     // memory for result low
sub_mul_int16_res2: .byte 0                     // memory for result high
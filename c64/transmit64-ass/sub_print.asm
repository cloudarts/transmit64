.importonce

// prints text to the screen
// in:
//      mem $FB: low byte of the start address of 0-terminated string
//      mem $FC: high byte of the start address of 0-terminated string
//      X: the column of the printed text
//      Y: the row of the printed text
//  out:
//      -
//  changes: A, X, Y, $FD, $FE

.import source "sub_mul.asm"
.import source "sub_petscii2screencode.asm"

.const SCR_BEGIN_H = $04 // the screen buffer starts at $0400 (40x25)
.const NUM_COLS = 40
                    
                    // reset vars
sub_print:          stx sub_print_save_x
                    lda #0
                    sta $FD
                    lda #SCR_BEGIN_H
                    sta $FE
                    
                    // compute the print start address:
                    // 1. add rows to $0400
                    lda #NUM_COLS
                    sta sub_mul_int16_val1  // store val1 for mul16: NUM_COLS
                    sty sub_mul_int16_val2  // store val2 for mul16: row
                    jsr sub_mul_int16
                    clc
                    lda sub_mul_int16_res1
                    sta $FD                 // low byte of print pos is 0, no need to add
                    lda sub_mul_int16_res2
                    adc $FE
                    sta $FE
                    // 2. add cols
                    clc
                    lda sub_print_save_x
                    adc $FD
                    sta $FD
                    lda #0
                    adc $FE
                    sta $FE

                    // start printing
                    ldy #0
sub_print_loop:     lda ($FB),y             // load character
                    cmp #0  
                    beq sub_print_exit
                    jsr sub_petscii2screencode
                    sta ($FD),y             // write to screen
                    iny
                    jmp sub_print_loop
                    
sub_print_exit:     rts

sub_print_save_x:   .byte 0
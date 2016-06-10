.importonce

// converts petscii char to screencode
// according to http://sta.c64.org/cbm64pettoscr.html

// in:
//      A: ascii char
// out: 
//      A: screencode char

sub_petscii2screencode:         cmp #$20
                                bmi bracket0
                                cmp #$40
                                bmi bracket1
                                cmp #$60
                                bmi bracket2
                                cmp #$80
                                bmi bracket3
                                cmp #$a0
                                bmi bracket4
                                cmp #$c0
                                bmi bracket5
                                cmp #$e0
                                bmi bracket6
                                cmp #$ff
                                bmi bracket7
                                jmp bracket8
                        
bracket0:                       adc #$80
bracket1:                       jmp sub_petscii2screencode_exit
bracket2:                       adc #$c0
                                jmp sub_petscii2screencode_exit
bracket3:                       adc #$e0
                                jmp sub_petscii2screencode_exit
bracket4:                       adc #$40
                                jmp sub_petscii2screencode_exit
bracket5:                       adc #$c0
                                jmp sub_petscii2screencode_exit
bracket6:                       adc #$80
                                jmp sub_petscii2screencode_exit
bracket7:                       adc #$80
                                jmp sub_petscii2screencode_exit
bracket8:                       lda #$5e
                                jmp sub_petscii2screencode_exit
                
sub_petscii2screencode_exit:    rts
.importonce

// simple INPUT for max 16 characters
// in: -
// will change A, X
// out: X length of str

.const KEY_ENTER = $0D
.const MAX_LENGTH = 16

sub_input:			ldx #0
					stx sub_input_counter	// reset sub_input_counter
sub_input_loop:		jsr $ff9f				// read keyboard, uses a,x,y
					jsr $FFE4   			// make keycode, uses a,x,y
					cmp #0         
					beq sub_input_loop 		// nothing entered, restart loop   
					cmp #KEY_ENTER			// ENTER key?
					beq sub_input_end		// --> finish input
					ldx sub_input_counter
					sta sub_input_buff, x	// save char
					jsr $ffd2				// print char, does not use x or y
					inx						// increment lenght sub_input_counter
					stx sub_input_counter
					cpx #MAX_LENGTH			// MAX_LENGTH reached?
					beq sub_input_end	  	// --> finish
					jmp sub_input_loop		// start loop from top

sub_input_end:		lda #0					// append terminator char
					ldx sub_input_counter
					sta sub_input_buff, x	
					rts
					
sub_input_counter:	.byte 0
sub_input_buff:		.fill MAX_LENGTH+1, 0			// generates 16 zero-bytes as buffer, +1 for \0
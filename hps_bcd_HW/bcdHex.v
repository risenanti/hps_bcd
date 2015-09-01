module bcdHex (

		input  [3:0] binary,
		output [6:0] seven_seg
    
);


	wire [3:0] fsm;
	reg [6:0] display;
	
	assign fsm = binary;
	//assign display = seven_seg;

	always @(*) 
		begin
		
			case(fsm)
				'b0000: display = 'b1000000; //'0'
				'b0001: display = 'b1111001; //'1'
				'b0010: display = 'b0100100; //'2'
				'b0011: display = 'b0110000; //'3'
				'b0100: display = 'b0011001; //'4'
				'b0101: display = 'b0010010; //'5'
				'b0110: display = 'b0000010; //'6'
				'b0111: display = 'b1111000; //'7'
				'b1000: display = 'b0000000; //'8'
				'b1001: display = 'b0011000; //'9'
			endcase
		end
		
		assign seven_seg = display;
		
endmodule

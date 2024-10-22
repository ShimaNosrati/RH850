# Configure CAN in RH850/U2A
				
VCU CAN	    Tx:	    P2_4 (E15)	CAN3_Tx	TCAN1043ADMTRQ1
	        Rx:	    P2_5 (D15)	CAN3_Rx	
	        En:	    P2_7 (D14)	Port/Out/H	
	        STBn:	P2_1 (C19)	Port/Out/H	
	        Err:	P2_8 (B14)	Port/In	

TBOX CAN	Tx:	    P2_3 (D16)	CAN4_Tx	TCAN1044AVDRBRQ1
	        Rx:	    P2_2 (B17)	CAN4_Rx	
	        STB:	P2_6 (E14)	NC:(GND) or Port/Out/L 	

Radar CAN	Tx:	    P3_4 (W18)	CAN7_Tx	TCAN1044AVDRBRQ1
	        Rx:	    P3_5 (W19)	CAN7_Rx	
	        STB:	P6_6 (R19)	NC:(GND) or Port/Out/L 	

Debug CAN 	Tx:	    P6_8 (P20)	CAN1_Tx	TCAN1044AVDRBRQ1
	        Rx:	    P6_7 (P19)	CAN1_Rx	
	        STB:	P6_12 (N19)	NC:(GND) or Port/Out/L 	
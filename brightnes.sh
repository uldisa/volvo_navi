#!/usr/bin/bash
X40=64
B100000=32
B10000=16
enable=0
enable=$B100000
display_on=0
#display_on=$B10000
for (( backlight=0 ; backlight<16 ; backlight++ )) ; do
	#b = enable (0b100000 or 0b0) + display_on (0x0 or 0b10000) + backlight (0b0000 (0) to 0b1111 (15)) ): 
	b=$(( $enable + $display_on + $backlight )) 
	parity=0
	for ((a=0; a<6; a++ )) ; do
		parity=$(( parity ^= (( b >> a ) & 1 ) ))
	done	
	# 0x40 == 64
	b=$(( (((~ parity) << 6) & $X40) + b )) 
	printf "%s\t%.2X\n" $backlight $b
done

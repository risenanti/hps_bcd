#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "hwlib.h"
#include "socal/socal.h"
#include "socal/hps.h"
#include "socal/alt_gpio.h"
#include "hps_0.h"

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

int main() {

	void *virtual_base;
	int fd;
	int loop_count;
	//int led_direction;
	int led_mask;
	void *h2p_lw_led_addr;

	int led_count = 0;

	// map the address space for the LED registers into user space so we can interact with them.
	// we'll actually map in the entire CSR span of the HPS since we want to access various registers within that span

	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return( 1 );
	}

	virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );

	if( virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap() failed...\n" );
		close( fd );
		return( 1 );
	}

	h2p_lw_led_addr=virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + PIO_LED_BASE ) & ( unsigned long)( HW_REGS_MASK ) );


	loop_count = 0;





	while( loop_count < 60 ) {

		// control led
		*(uint32_t *)h2p_lw_led_addr = ~led_mask;

		// wait 100ms
		usleep( 1000*1000 );

		// update led mask
			//led_mask = 0b0011; //3
//if (led_mask == (0x01 << (PIO_LED_DATA_WIDTH-1)))
		//0x00;
		//0x01
		//0x0000
		//0x0001
		//0x0010

		switch(led_count)
		{
			case 0:  led_mask = 0b1111; break;
			case 1:  led_mask = 0b1110; break;
			case 2:  led_mask = 0b1101; break;
			case 3:  led_mask = 0b1100; break;
			case 4:  led_mask = 0b1011; break; //9
			case 5:  led_mask = 0b1010; break; //correct
			case 6:  led_mask = 0b1001; break; //correct
			case 7:  led_mask = 0b1000; break; //correct
			case 8:  led_mask = 0b0111; break; //correct
			case 9:  led_mask = 0b0110; break; //correct
			default: led_mask = 0b0000; break;
		}
/*0x0000000000000004
			case 0:  led_mask = 0x0000000000000000; break;
			case 1:  led_mask = 0x000000000000000; break;
			case 2:  led_mask = 0x0010; break;
			case 3:  led_mask = 0x0011; break;
			case 4:  led_mask = 0b00000100; break;
			case 5:  led_mask = 0b00000101; break;
			case 6:  led_mask = 0b00001001; break; //correct
			case 7:  led_mask = 0b00001000; break; //correct
			case 8:  led_mask = 0b00000111; break; //correct
			case 9:  led_mask = 0b00000110; break; //correct
			default: led_mask = 0b00000000; break;
*/

		printf("%d\n",led_count);
		led_count++;
		//usleep( 1000*1000 );
		if (led_count>9)
		{
			led_count=0;
		}


	} // while


	// clean up our memory mapping and exit

	if( munmap( virtual_base, HW_REGS_SPAN ) != 0 ) {
		printf( "ERROR: munmap() failed...\n" );
		close( fd );
		return( 1 );
	}

	close( fd );

	return( 0 );
}

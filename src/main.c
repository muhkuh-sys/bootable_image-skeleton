
#include "netx_io_areas.h"
#include "version.h"
#include "uart_standalone.h"
#include "uprintf.h"


/*-------------------------------------------------------------------------*/


/* This is a macro which defines a set of global variables for the UART
 * communication.
 */
UART_STANDALONE_DEFINE_GLOBALS


/* This function is called from the assembler source "init.S". It does not
 * need a header file.
 */
void image_main(void) __attribute__ ((noreturn));


/* This is the main function. */
void image_main(void)
{
	const char *pcPlatformName;


	/* Initialize the UART routines. */
	uart_standalone_initialize();

	/* Show a welcome message on the UART. */
	uprintf("\f. *** Bootable image skeleton by cthelen@hilscher.com ***\n");
	uprintf("V" VERSION_ALL "\n\n");

	/* Print the platform name. */
#if ASIC_TYP==ASIC_TYP_NETX500
	pcPlatformName = "netX500/100";
#elif ASIC_TYP==ASIC_TYP_NETX50
	pcPlatformName = "netX50";
#elif ASIC_TYP==ASIC_TYP_NETX56
	pcPlatformName = "netX51/52";
#elif ASIC_TYP==ASIC_TYP_NETX10
	pcPlatformName = "netX10";
#elif ASIC_TYP==ASIC_TYP_NETX4000_RELAXED
	pcPlatformName = "netX4000 RELAXED";
#elif ASIC_TYP==ASIC_TYP_NETX90_MPW
	pcPlatformName = "netX90 MPW COM CPU";
#elif ASIC_TYP==ASIC_TYP_NETX90_MPW_APP
	pcPlatformName = "netX90 MPW APP CPU";
#else
#       error "Add your platform here."
#endif
	uprintf("Running on %s.\n", pcPlatformName);

	/* Stop here. */
	while(1) {};
}

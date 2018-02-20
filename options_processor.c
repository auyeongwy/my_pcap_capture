/** @file options_processor.h
 * Implements functions to process application configuration options.
 */


#include <string.h>
#include "options_processor.h"
#include "err_processor.h"



int process_params(const int p_argc, char *const p_argv[], struct s_options *const p_options)
{
	int tmp; 
	
	if(p_argc < 3) { /* Not enough arguments. */
		set_err_msg("Usage:\nmy_pcap_capture file <file path>\nmy_pcap_capture live <interface>\nCtrl-C to interrupt.\n");
		return -1;
	}
	
	/* Check if "file" or "live" mode is specified in the argument list. Fill in p_options->capture_type */
	if(strcmp(p_argv[1], "file")==0)
		p_options->capture_type = FILE_CAPTURE;
	else if(strcmp(p_argv[1], "live")==0)
		p_options->capture_type = INTERFACE_CAPTURE;
	else {
		set_err_msg("Usage:\nmy_pcap_capture file <file path>\nmy_pcap_capture live <interface>\nCtrl-C to interrupt.\n");
		return -1;		
	}
	
	/* Fill in p_options->target */
	if((tmp = strlen(p_argv[2])) > 255) {
		set_err_msg("Target length too long\n");
		return -1;
	} else {
		strncpy(p_options->target, p_argv[2], tmp);
		p_options->target[tmp] = 0;
	}
	
	return 0;
}

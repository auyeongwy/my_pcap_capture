/* Copyright 2018 Au Yeong Wing Yau

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
 */


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

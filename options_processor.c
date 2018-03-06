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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include "options_processor.h"
#include "mpc_output.h"

#define OPTIONS_FILE "options.config"

/** Read keyvalues of the form key=value from the options file.
 *  @param p_ptions Options structure where the values will be filled.
 */
static int read_options_file(struct s_options *const __restrict__ p_options);

/** Read all key values of the form key=value from the provided buffer.
 *  @param p_buffer Buffer to read the keyvalues from.
 *  @param p_ptions Options structure where the values will be filled.
 *  @return 0 if success. Else -1.
 */
static int read_key_values(char *__restrict__ p_buffer, struct s_options *const __restrict__ p_options);

/** Read a specific value from a key of the form key=value from the provided buffer using a regex expression.
 *  @param p_buffer The buffer to read the key-vaue from.
 *  @param p_regex The regex expression to read out the keyvalue. The value must be enclosed in (), as per regex rules.
 *  @param p_value The keyvalue is written back into this buffer.
 *  @param p_len p_len The length of p_value.
 *  @return The length of p_value if successful. 0 if value not found. -1 if some error - the error message is set in the error buffer (see mpc_output.h).
 */
static int read_key_value(char *__restrict__ p_buffer, const char *__restrict__ p_regex, char *__restrict__ p_value, const int p_len);



int process_params(const int p_argc, char *const p_argv[], struct s_options *const __restrict__ p_options)
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
	
	if(read_options_file(p_options) == -1)
		print_err();
	
	return 0;
}



static int read_options_file(struct s_options *const __restrict__ p_options)
{
	struct stat stat_buf;
	char *file_buf = NULL;
	FILE *f = NULL;
	int ret = -1;
	
	if(stat(OPTIONS_FILE, &stat_buf) != 0) {
		set_errno_msg("Options file error: ");
		return -1;
	}
	
	if((file_buf = malloc(stat_buf.st_size)) == NULL) {
		set_errno_msg("Options file error: ");
		goto do_exit;		
	}
	
	if((f = fopen(OPTIONS_FILE, "r")) == NULL) {
		set_errno_msg("Options file error: ");
		goto do_exit;
	}

	fread(file_buf, 1, stat_buf.st_size, f);
	ret = read_key_values(file_buf, p_options);
	
do_exit:
	if(file_buf != NULL)
		free(file_buf);
	if(f != NULL)
		fclose(f);
	return ret;
}



static int read_key_values(char *__restrict__ p_buffer, struct s_options *const __restrict__ p_options)
{
	int ret;
	
	if((ret = read_key_value(p_buffer, "ixEngine=([^\n]+)", p_options->options, 256))>0) {
		return 0;
	} else if (ret < 0)
		print_err();
	
	return -1;
}



static int read_key_value(char *__restrict__ p_buffer, const char *__restrict__ p_regex, char *__restrict__ p_value, const int p_len)
{
	regex_t re; /* The regex expression. */
	regmatch_t matches[2]; /* Regext matched strings. */
	int ret=0, len; 
	char *char_ptr;
	

	if((ret = regcomp(&re, p_regex, REG_EXTENDED)) != 0) { /* Compile the regex expression. */
		set_err_msg("Regcomp error\n");
		ret = -1;
		goto do_exit;
	} 
	
	
	if(regexec(&re, p_buffer, 2, matches, 0) == 0) { /* Perform the match. */
		/* Get the value match. */
		char_ptr = p_buffer + matches[1].rm_so;
		if((len = matches[1].rm_eo - matches[1].rm_so) >= p_len) {
			set_err_msg("Value too long");
			ret = -1;
			goto do_exit;
		}
		memcpy(p_value, char_ptr, len);
		p_value[len] = 0;
		ret = len;
	}
	
do_exit:
	regfree(&re);
	return ret;
}

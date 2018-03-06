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


/** @file mpc_output.c
 * Implements functions to perform output functions. Note this version is not thread-safe.
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "mpc_output.h"

#define ERR_MSG_LEN 128 /**< Error message buffer length. */
static char v_err_msg[ERR_MSG_LEN]; /**< Error message buffer. */
static int v_err_offset;


void set_err_msg(const char *const __restrict__ p_msg)
{
	int len = strlen(p_msg);
	if(len > (ERR_MSG_LEN-1)) 
		len = ERR_MSG_LEN-1;
	strncpy(v_err_msg, p_msg, len);
	v_err_offset = len;
	v_err_msg[len+1] = 0;
}



void concat_err_msg(const char *const __restrict__ p_msg)
{
	int len = strlen(p_msg);
	if(len + v_err_offset > (ERR_MSG_LEN-1)) 
		len = ERR_MSG_LEN - 1 -v_err_offset;
	strncpy(v_err_msg + v_err_offset, p_msg, len);	
	v_err_offset += len;
	v_err_msg[v_err_offset+1] = 0;
}



char* get_err_msg()
{
	return v_err_msg;
}



void set_errno_msg(const char *const __restrict__ p_header)
{
	if(p_header != NULL) {
		set_err_msg(p_header);
		concat_err_msg(strerror(errno));
	} else
		set_err_msg(strerror(errno));
}



void print_err()
{
	fprintf(stderr, v_err_msg);
	fprintf(stderr, "\n");
	v_err_msg[0] = 0;
	v_err_offset = 0;
}
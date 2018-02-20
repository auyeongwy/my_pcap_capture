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


/** @file err_processor.c
 * Implements functions to process error messages. Note this version is not thread-safe.
 */

#include <string.h>
#include "err_processor.h"

#define ERR_MSG_LEN 128 /**< Error message buffer length. */
static char v_err_msg[ERR_MSG_LEN]; /**< Error message buffer. */



void set_err_msg(const char *p_msg)
{
	int len = strlen(p_msg);
	if(len > (ERR_MSG_LEN-1)) 
		len = ERR_MSG_LEN-1;
	strncpy(v_err_msg, p_msg, len);
	v_err_msg[len+1] = 0;
}



char* get_err_msg()
{
	return v_err_msg;
}

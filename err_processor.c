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

/** @file err_processor.h
 * Implements functions to process error messages. Note this version is not thread-safe.
 */


#ifndef _ERR_PROCESSOR_H_
#define _ERR_PROCESSOR_H_

/** Set an error message in the error buffer. Note that this can be overwritten if it is called again.
 * @p_msg Message to write in the error buffer.
 */
void set_err_msg(const char *p_msg);

/** Get the error message in the error buffer.
 *  @return Error message in the error buffer.
 */
char* get_err_msg();


#endif
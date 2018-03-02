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


/** @file mpc_output.h
 * Implements functions to perform output functions. Note this version is not thread-safe.
 */


#ifndef _MPC_OUTPUT_H_
#define _MPC_OUTPUT_H_

/** Set an error message in the error buffer. Note that this can be overwritten if it is called again.
 * @p_msg Message to write in the error buffer.
 */
void set_err_msg(const char *p_msg);

/** Get the error message in the error buffer.
 *  @return Error message in the error buffer.
 */
char* get_err_msg();


#endif
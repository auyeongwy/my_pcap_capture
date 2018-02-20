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

#ifndef _OPTIONS_PROCESSOR_H_
#define _OPTIONS_PROCESSOR_H_

enum 
{
	FILE_CAPTURE, /**< Pcap file reading operation. */
	INTERFACE_CAPTURE /**< Live capture operation. */
};


/**
 * Structure that contains configuration options for the application.
 */
struct s_options {
	int capture_type; /**< Indicates a capture type. See enum above. */
	char target[256]; /**< Capture target. File path of interface name. */
};

/** Process parameters from the command line and initialize configuration options. Also examines configuration for errors.
 * @p_argc The argc from main().
 * @p_argv The argv from main().
 * @p_options Configuration options will be written into this structure.
 * @return 0 if success. Else -1, and an error message will be written to the error buffer. Use get_err_msg() to retrieve.
 */
int process_params(const int p_argc, char *const p_argv[], struct s_options *const p_options);


#endif
/* Klunk request, handling the state of a FCGI request.
 *(C) 2014 Erik Svensson <erik.public@gmail.com>
 * Licensed under the MIT license.
 */

#ifndef KLUNK_REQUEST_H
#define KLUNK_REQUEST_H

#include <stdint.h>
#include "llist.h"
#include "buffer.h"

enum {
	KLUNK_RS_INIT				= 0,
	KLUNK_RS_NEW				= 1,
	KLUNK_RS_PARAMS				= (1 << 1),
	KLUNK_RS_PARAMS_DONE		= (1 << 2),
	KLUNK_RS_STDIN				= (1 << 3),
	KLUNK_RS_STDIN_DONE			= (1 << 4),
	KLUNK_RS_STDOUT				= (1 << 5),
	KLUNK_RS_STDOUT_DONE		= (1 << 6),
	KLUNK_RS_STDERR				= (1 << 7),
	KLUNK_RS_STDERR_DONE		= (1 << 8),
	KLUNK_RS_FINISHED			= (1 << 9),
	KLUNK_RS_WRITE_FINISHED		= (1 << 10)
};

typedef struct klunk_request_  {
	uint16_t        id;
	uint16_t        role;
	uint16_t		state;
	uint8_t         flags;
	uint8_t         protocol_status;
	uint32_t		app_status;
	llist_t			*params;
	buffer_t		*content;
	buffer_t		*output;
	buffer_t		*error;
} klunk_request_t;

/* Create a request "object" */
klunk_request_t* klunk_request_create();

/* Destroy the request "object" */
void klunk_request_destroy(klunk_request_t *request);

/* Get request state */
int32_t klunk_request_get_state(klunk_request_t *request, const uint16_t mask);

/* Set request state */
int32_t klunk_request_set_state(klunk_request_t *request, const uint16_t state);

int32_t klunk_request_generate_record(klunk_request_t *request
	, char *output, const int32_t output_len
	, const uint8_t type
	, const char *input, const int32_t input_len);

/* 
 * Negative return value means error.
 */
int32_t klunk_request_write_output(klunk_request_t *request
	, const char *input, const size_t input_len);

/* 
 * Negative return value means error.
 */
int32_t klunk_request_write_error(klunk_request_t *request
	, const char *input, const size_t input_len);

/* 
 * Negative return value means error.
 */
int32_t klunk_request_read(klunk_request_t *request
	, char *output, const size_t output_len);

/* 
 * Negative return value means error.
 */
int32_t klunk_request_finish(klunk_request_t *request
	, const uint32_t app_status, const uint8_t protocol_status);

#endif /* KLUNK_REQUEST_H */

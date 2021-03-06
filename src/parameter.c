#include "parameter.h"
#include "errorcodes.h"

#include <string.h>

fastcgi_parameter_t* fastcgi_parameter_create(const char *name, const size_t name_len
	, const char *value, const size_t value_len)
{
	int32_t result = E_SUCCESS;
	fastcgi_parameter_t *param = 0;
	param = malloc(sizeof(fastcgi_parameter_t));
	if (param != 0) {
		param->name = 0;
		param->name_len = 0;
		param->name_allocated = 0;
		param->value = 0;
		param->value_len = 0;
		param->value_allocated = 0;

		result = fastcgi_parameter_set(param, name, name_len, value, value_len);
		if (result != E_SUCCESS) {
			fastcgi_parameter_destroy(param);
			param = 0;
		}
	}
	return param;
}

void fastcgi_parameter_destroy(fastcgi_parameter_t *param)
{
	if (param != 0) {
		if (param->name_allocated > 0) {
			free(param->name);
			param->name = 0;
			param->name_len = 0;
			param->name_allocated = 0;
		}
		if (param->value_allocated > 0) {
			free(param->value);
			param->value = 0;
			param->value_len = 0;
			param->value_allocated = 0;
		}
		free(param);
	}
}

/* Set the key/value pair */
int32_t fastcgi_parameter_set(fastcgi_parameter_t* param
	, const char *name, const size_t name_len
	, const char *value, const size_t value_len)
{
	int32_t result = E_SUCCESS;
	size_t alloc_len = 0;

	if (param == 0) {
		result = E_INVALID_OBJECT;
	}
	if (result == E_SUCCESS) {
		if (name_len >= param->name_allocated) {
			free(param->name);
			param->name = 0;
			param->name_allocated = 0;
			alloc_len = ((name_len / 32) + 1) * 32;
			param->name = malloc(alloc_len);
			if (param->name != 0) {
				param->name_allocated = alloc_len;
			}
			else {
				result = E_MEMORY_ALLOCATION_FAILED;
			}
		}
	}
	if (result == E_SUCCESS) {
		param->name_len = name_len;
		memcpy(param->name, name, param->name_len);
		param->name[param->name_len] = 0;
	}
	if (result == E_SUCCESS) {
		if (value_len >= param->value_allocated) {
			free(param->value);
			param->value = 0;
			param->value_allocated = 0;
			alloc_len = ((value_len / 128) + 1) * 128;
			param->value = malloc(alloc_len);
			if (param->value != 0) {
				param->value_allocated = alloc_len;
			}
			else {
				result = E_MEMORY_ALLOCATION_FAILED;
			}
		}
	}
	if (result == E_SUCCESS) {
		param->value_len = value_len;
		memcpy(param->value, value, param->value_len);
		param->value[param->value_len] = 0;
	}
	return result;
}

/* Clear the key/value pair */
int32_t fastcgi_parameter_reset(fastcgi_parameter_t* param)
{
	int32_t result = E_SUCCESS;
	if (param == 0) {
		result = E_INVALID_OBJECT;
	}
	else {
		param->name_len = 0;
		param->value_len = 0;
		if (param->name_allocated > 0) {
			param->name[0] = 0;
		}
		if (param->value_allocated > 0) {
			param->value[0] = 0;
		}
	}
	return result;
}

int32_t fastcgi_parameter_is_free(fastcgi_parameter_t *param)
{
	if (param == 0) {
		return E_INVALID_OBJECT;
	}
	return param->name_len == 0 && param->value_len == 0;
}
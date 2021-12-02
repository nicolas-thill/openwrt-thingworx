#include <twOSPort.h>
#include <twLogger.h>
#include <twApi.h>
#include <twMacros.h>
#include <twPath.h>
#include <twExt.h>
#include <twMacros.h>

enum msgCodeEnum addNumbersService(const char* entityName, const char* serviceName, twInfoTable* params, twInfoTable** content, void* userData);

void createClientThing(char* thingName);

/********************** Service Implementations **********************/
/** Handling a single service in a callback, this functions adds two numbers and returns their sum. */

enum msgCodeEnum addNumbersService(const char* entityName, const char* serviceName, twInfoTable* params, twInfoTable** content, void* userData) {
	double a, b, res;

	TW_LOG(TW_TRACE, "addNumbersService: function called");
	if (!params || !content) {
		TW_LOG(TW_ERROR, "addNumbersService: NULL params or content");
		return TWX_BAD_REQUEST;
	}

	/* Get the parameters */
	twInfoTable_GetNumber(params, "a", 0, &a);
	twInfoTable_GetNumber(params, "b", 0, &b);

	/* perform the calculation */
	res = a + b;

	/* Return Results */
	*content = twInfoTable_CreateFromNumber("result", res);
	if (!*content) {
		TW_LOG(TW_ERROR, "addNumbersService: internal server error");
		return TWX_INTERNAL_SERVER_ERROR;
	}

	return TWX_SUCCESS;
}


/**
 * This function defines a thing. Multiple instances of this thing can be declared by changing the
 * thingName parameter.
 */
void createClientThing(char* thingName) {

	/********************** Declare Properties **********************/
	TW_MAKE_THING(thingName, TW_THING_TEMPLATE_GENERIC);

	/********************** Register Services **********************/

	TW_SERVICE("AddNumbers",
		"Add two numbers together",
		TW_MAKE_DATASHAPE(TW_SHAPE_NAME_NONE,
			TW_DS_ENTRY("a", TW_NO_DESCRIPTION, TW_NUMBER),
			TW_DS_ENTRY("b", TW_NO_DESCRIPTION, TW_NUMBER)
		),
		TW_NUMBER,
		TW_NO_RETURN_DATASHAPE,
		addNumbersService
	);

	TW_BIND();
}





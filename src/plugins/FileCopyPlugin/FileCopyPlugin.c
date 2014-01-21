/* Smalltalk from Squeak4.5 with VMMaker 4.12.14 translated as C source on 20 January 2014 7:15:37 pm */
/* Automatically generated by
	SmartSyntaxPluginCodeGenerator VMMaker-dtl.338 uuid: 29946156-9015-45c9-83a2-c12d43f67ece
   from
	FileCopyPlugin VMMaker-dtl.338 uuid: 29946156-9015-45c9-83a2-c12d43f67ece
 */
static char __buildInfo[] = "FileCopyPlugin VMMaker-dtl.338 uuid: 29946156-9015-45c9-83a2-c12d43f67ece " __DATE__ ;




#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
/*  The virtual machine proxy definition */
#include "sqVirtualMachine.h"
/* Configuration options */
#include "sqConfig.h"
/* Platform specific definitions */
#include "sqPlatformSpecific.h"

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
#undef EXPORT
// was #undef EXPORT(returnType) but screws NorCroft cc
#define EXPORT(returnType) static returnType
#endif

#include "sqMemoryAccess.h"


/*** Constants ***/

/*** Function Prototypes ***/
#pragma export on
EXPORT(const char*) getModuleName(void);
#pragma export off
static sqInt halt(void);
#pragma export on
EXPORT(sqInt) primitiveFileCopyNamedTo(void);
EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter);
#pragma export off
/*** Variables ***/

#ifdef SQUEAK_BUILTIN_PLUGIN
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"FileCopyPlugin 20 January 2014 (i)"
#else
	"FileCopyPlugin 20 January 2014 (e)"
#endif
;



/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

EXPORT(const char*) getModuleName(void) {
	return moduleName;
}

static sqInt halt(void) {
	;
}

EXPORT(sqInt) primitiveFileCopyNamedTo(void) {
	sqInt srcSz;
	sqInt dstSz;
	sqInt ok;
	char *srcName;
	char *dstName;

	interpreterProxy->success(interpreterProxy->isBytes(interpreterProxy->stackValue(1)));
	srcName = ((char *) (interpreterProxy->firstIndexableField(interpreterProxy->stackValue(1))));
	interpreterProxy->success(interpreterProxy->isBytes(interpreterProxy->stackValue(0)));
	dstName = ((char *) (interpreterProxy->firstIndexableField(interpreterProxy->stackValue(0))));
	if (interpreterProxy->failed()) {
		return null;
	}
	srcSz = interpreterProxy->slotSizeOf((oopForPointer( srcName ) - BASE_HEADER_SIZE));
	dstSz = interpreterProxy->slotSizeOf((oopForPointer( dstName ) - BASE_HEADER_SIZE));
	ok = sqCopyFilesizetosize(srcName, srcSz, dstName, dstSz);
	if (!(ok)) {
		interpreterProxy->primitiveFail();
	}
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->pop(2);
	return null;
}


/*	Note: This is coded so that is can be run from Squeak. */

EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter) {
	sqInt ok;

	interpreterProxy = anInterpreter;
	ok = interpreterProxy->majorVersion() == VM_PROXY_MAJOR;
	if (ok == 0) {
		return 0;
	}
	ok = interpreterProxy->minorVersion() >= VM_PROXY_MINOR;
	return ok;
}


#ifdef SQUEAK_BUILTIN_PLUGIN


void* FileCopyPlugin_exports[][3] = {
	{"FileCopyPlugin", "setInterpreter", (void*)setInterpreter},
	{"FileCopyPlugin", "getModuleName", (void*)getModuleName},
	{"FileCopyPlugin", "primitiveFileCopyNamedTo", (void*)primitiveFileCopyNamedTo},
	{NULL, NULL, NULL}
};


#endif /* ifdef SQ_BUILTIN_PLUGIN */


/* Automatically generated by
	VMPluginCodeGenerator VMMaker.oscog-eem.2079 uuid: 00ef0ca2-fca0-4dc0-baa9-e65e98fda15a
   from
	StarSqueakPlugin VMMaker.oscog-eem.2079 uuid: 00ef0ca2-fca0-4dc0-baa9-e65e98fda15a
 */
static char __buildInfo[] = "StarSqueakPlugin VMMaker.oscog-eem.2079 uuid: 00ef0ca2-fca0-4dc0-baa9-e65e98fda15a " __DATE__ ;



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
#include "sqConfig.h"			/* Configuration options */
#include "sqVirtualMachine.h"	/*  The virtual machine proxy definition */
#include "sqPlatformSpecific.h"	/* Platform specific definitions */

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
# undef EXPORT
# define EXPORT(returnType) static returnType
#endif

#include "sqMemoryAccess.h"


/*** Function Prototypes ***/
static unsigned int * checkedUnsignedIntPtrOf(sqInt oop);
EXPORT(const char*) getModuleName(void);
EXPORT(sqInt) primitiveDiffuseFromToWidthHeightDelta(void);
EXPORT(sqInt) primitiveEvaporateRate(void);
EXPORT(sqInt) primitiveMapFromToWidthHeightPatchSizeRgbFlagsShift(void);
EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter);


/*** Variables ***/

#if !defined(SQUEAK_BUILTIN_PLUGIN)
static sqInt (*failed)(void);
static void * (*firstIndexableField)(sqInt oop);
static sqInt (*isWords)(sqInt oop);
static sqInt (*pop)(sqInt nItems);
static sqInt (*stSizeOf)(sqInt oop);
static sqInt (*stackIntegerValue)(sqInt offset);
static sqInt (*stackValue)(sqInt offset);
static sqInt (*success)(sqInt aBoolean);
#else /* !defined(SQUEAK_BUILTIN_PLUGIN) */
extern sqInt failed(void);
extern void * firstIndexableField(sqInt oop);
extern sqInt isWords(sqInt oop);
extern sqInt pop(sqInt nItems);
extern sqInt stSizeOf(sqInt oop);
extern sqInt stackIntegerValue(sqInt offset);
extern sqInt stackValue(sqInt offset);
extern sqInt success(sqInt aBoolean);
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"StarSqueakPlugin VMMaker.oscog-eem.2079 (i)"
#else
	"StarSqueakPlugin VMMaker.oscog-eem.2079 (e)"
#endif
;



/*	Return an unsigned int pointer to the first indexable word of oop, which
	must be a words object.
 */

	/* StarSqueakPlugin>>#checkedUnsignedIntPtrOf: */
static unsigned int *
checkedUnsignedIntPtrOf(sqInt oop)
{
	success(isWords(oop));
	if (failed()) {
		return 0;
	}
	return ((unsigned int *) (firstIndexableField(oop)));
}


/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

	/* InterpreterPlugin>>#getModuleName */
EXPORT(const char*)
getModuleName(void)
{
	return moduleName;
}


/*	Diffuse the integer values of the source patch variable Bitmap into the
	output Bitmap. Each cell of the output is the average of the NxN area
	around it in the source, where N = (2 * delta) + 1.
 */

	/* StarSqueakPlugin>>#primitiveDiffuseFromToWidthHeightDelta */
EXPORT(sqInt)
primitiveDiffuseFromToWidthHeightDelta(void)
{
    sqInt area;
    sqInt delta;
    unsigned int *dst;
    sqInt dstOop;
    sqInt endX;
    sqInt endY;
    sqInt height;
    sqInt rowStart;
    unsigned int *src;
    sqInt srcOop;
    sqInt startX;
    sqInt startY;
    sqInt sum;
    sqInt width;
    sqInt x;
    sqInt x2;
    sqInt y;
    sqInt y2;

	srcOop = stackValue(4);
	dstOop = stackValue(3);
	width = stackIntegerValue(2);
	height = stackIntegerValue(1);
	delta = stackIntegerValue(0);
	/* begin checkedUnsignedIntPtrOf: */
	success(isWords(srcOop));
	if (failed()) {
		src = 0;
		goto l1;
	}
	src = ((unsigned int *) (firstIndexableField(srcOop)));
l1:	/* end checkedUnsignedIntPtrOf: */;
	/* begin checkedUnsignedIntPtrOf: */
	success(isWords(dstOop));
	if (failed()) {
		dst = 0;
		goto l2;
	}
	dst = ((unsigned int *) (firstIndexableField(dstOop)));
l2:	/* end checkedUnsignedIntPtrOf: */;
	success((stSizeOf(srcOop)) == (stSizeOf(dstOop)));
	success((stSizeOf(srcOop)) == (width * height));
	if (failed()) {
		return null;
	}
	area = ((2 * delta) + 1) * ((2 * delta) + 1);
	for (y = 0; y < height; y += 1) {
		startY = y - delta;
		if (startY < 0) {
			startY = 0;
		}
		endY = y + delta;
		if (endY >= height) {
			endY = height - 1;
		}
		for (x = 0; x < width; x += 1) {
			startX = x - delta;
			if (startX < 0) {
				startX = 0;
			}
			endX = x + delta;
			if (endX >= width) {
				endX = width - 1;
			}
			sum = 0;
			for (y2 = startY; y2 <= endY; y2 += 1) {
				rowStart = y2 * width;
				for (x2 = startX; x2 <= endX; x2 += 1) {
					sum += src[rowStart + x2];
				}
			}
			dst[(y * width) + x] = (sum / area);
		}
	}
	pop(5);
	return 0;
}


/*	Evaporate the integer values of the source Bitmap at the given rate. The
	rate is an integer between 0 and 1024, where 1024 is a scale factor of 1.0
	(i.e., no evaporation).
 */

	/* StarSqueakPlugin>>#primitiveEvaporateRate */
EXPORT(sqInt)
primitiveEvaporateRate(void)
{
    sqInt i;
    unsigned int *patchVar;
    sqInt patchVarOop;
    sqInt rate;
    sqInt sz;

	patchVarOop = stackValue(1);
	rate = stackIntegerValue(0);
	/* begin checkedUnsignedIntPtrOf: */
	success(isWords(patchVarOop));
	if (failed()) {
		patchVar = 0;
		goto l1;
	}
	patchVar = ((unsigned int *) (firstIndexableField(patchVarOop)));
l1:	/* end checkedUnsignedIntPtrOf: */;
	sz = stSizeOf(patchVarOop);
	if (failed()) {
		return null;
	}
	for (i = 0; i < sz; i += 1) {
		patchVar[i] = (((usqInt) ((patchVar[i]) * rate)) >> 10);
	}
	pop(2);
	return 0;
}

	/* StarSqueakPlugin>>#primitiveMapFromToWidthHeightPatchSizeRgbFlagsShift */
EXPORT(sqInt)
primitiveMapFromToWidthHeightPatchSizeRgbFlagsShift(void)
{
    unsigned int *dst;
    sqInt dstIndex;
    sqInt dstOop;
    sqInt h;
    sqInt level;
    sqInt offset;
    sqInt patchSize;
    sqInt pixel;
    sqInt rgbFlags;
    sqInt rgbMult;
    sqInt rowStart;
    sqInt shiftAmount;
    unsigned int *src;
    sqInt srcIndex;
    sqInt srcOop;
    sqInt w;
    sqInt x;
    sqInt y;

	srcOop = stackValue(6);
	dstOop = stackValue(5);
	w = stackIntegerValue(4);
	h = stackIntegerValue(3);
	patchSize = stackIntegerValue(2);
	rgbFlags = stackIntegerValue(1);
	shiftAmount = stackIntegerValue(0);
	/* begin checkedUnsignedIntPtrOf: */
	success(isWords(srcOop));
	if (failed()) {
		src = 0;
		goto l1;
	}
	src = ((unsigned int *) (firstIndexableField(srcOop)));
l1:	/* end checkedUnsignedIntPtrOf: */;
	/* begin checkedUnsignedIntPtrOf: */
	success(isWords(dstOop));
	if (failed()) {
		dst = 0;
		goto l2;
	}
	dst = ((unsigned int *) (firstIndexableField(dstOop)));
l2:	/* end checkedUnsignedIntPtrOf: */;
	success((stSizeOf(dstOop)) == (w * h));
	success((stSizeOf(dstOop)) == (((stSizeOf(srcOop)) * patchSize) * patchSize));
	if (failed()) {
		return null;
	}
	rgbMult = 0;
	if ((rgbFlags & 4) > 0) {
		rgbMult += 65536;
	}
	if ((rgbFlags & 2) > 0) {
		rgbMult += 256;
	}
	if ((rgbFlags & 1) > 0) {
		rgbMult += 1;
	}
	srcIndex = -1;
	for (y = 0; y < (h / patchSize); y += 1) {
		for (x = 0; x < (w / patchSize); x += 1) {
			level = ((shiftAmount < 0) ? ((usqInt) (src[(srcIndex += 1)]) >> -shiftAmount) : ((usqInt) (src[(srcIndex += 1)]) << shiftAmount));
			if (level > 0xFF) {
				level = 0xFF;
			}
			if (level <= 0) {

				/* non-transparent black */
				pixel = 1;
			}
			else {
				pixel = level * rgbMult;
			}
			offset = ((y * w) + x) * patchSize;
			for (rowStart = offset; rowStart <= (offset + ((patchSize - 1) * w)); rowStart += w) {
				for (dstIndex = rowStart; dstIndex < (rowStart + patchSize); dstIndex += 1) {
					dst[dstIndex] = pixel;
				}
			}
		}
	}
	pop(7);
	return 0;
}


/*	Note: This is coded so that it can be run in Squeak. */

	/* InterpreterPlugin>>#setInterpreter: */
EXPORT(sqInt)
setInterpreter(struct VirtualMachine*anInterpreter)
{
    sqInt ok;

	interpreterProxy = anInterpreter;
	ok = ((interpreterProxy->majorVersion()) == (VM_PROXY_MAJOR))
	 && ((interpreterProxy->minorVersion()) >= (VM_PROXY_MINOR));
	if (ok) {
		
#if !defined(SQUEAK_BUILTIN_PLUGIN)
		failed = interpreterProxy->failed;
		firstIndexableField = interpreterProxy->firstIndexableField;
		isWords = interpreterProxy->isWords;
		pop = interpreterProxy->pop;
		stSizeOf = interpreterProxy->stSizeOf;
		stackIntegerValue = interpreterProxy->stackIntegerValue;
		stackValue = interpreterProxy->stackValue;
		success = interpreterProxy->success;
#endif /* !defined(SQUEAK_BUILTIN_PLUGIN) */
	}
	return ok;
}


#ifdef SQUEAK_BUILTIN_PLUGIN

static char _m[] = "StarSqueakPlugin";
void* StarSqueakPlugin_exports[][3] = {
	{(void*)_m, "getModuleName", (void*)getModuleName},
	{(void*)_m, "primitiveDiffuseFromToWidthHeightDelta\000\001", (void*)primitiveDiffuseFromToWidthHeightDelta},
	{(void*)_m, "primitiveEvaporateRate\000\001", (void*)primitiveEvaporateRate},
	{(void*)_m, "primitiveMapFromToWidthHeightPatchSizeRgbFlagsShift\000\001", (void*)primitiveMapFromToWidthHeightPatchSizeRgbFlagsShift},
	{(void*)_m, "setInterpreter", (void*)setInterpreter},
	{NULL, NULL, NULL}
};

#else /* ifdef SQ_BUILTIN_PLUGIN */

signed char primitiveDiffuseFromToWidthHeightDeltaAccessorDepth = 1;
signed char primitiveEvaporateRateAccessorDepth = 1;
signed char primitiveMapFromToWidthHeightPatchSizeRgbFlagsShiftAccessorDepth = 1;

#endif /* ifdef SQ_BUILTIN_PLUGIN */

//metadoc Error copyright Rich Collins 2008
//metadoc Error license BSD revised
/*metadoc Error description
An object that contains error information and flow control based on errors.
*/

#include "IoError.h"
#include "IoState.h"
#include "IoSeq.h"

IoTag *IoError_newTag(void *state)
{
	IoTag *tag = IoTag_newWithName_("Error");
	IoTag_state_(tag, state);
	IoTag_cloneFunc_(tag, (IoTagCloneFunc *)IoError_rawClone);
	return tag;
}

IoError *IoError_proto(void *state)
{
	IoError *self = IoObject_new(state);
	IoObject_tag_(self, IoError_newTag(state));

	IoState_registerProtoWithFunc_(state, self, IoError_proto);

	{
		IoMethodTable methodTable[] = {
			{NULL, NULL}
		};
		IoObject_addMethodTable_(self, methodTable);
	}
	return self;
}

IoError *IoError_rawClone(IoError *proto)
{
	IoError *self = IoObject_rawClonePrimitive(proto);
	return self;
}

IoError *IoError_new(void *state)
{
	IoError *proto = IoState_protoWithInitFunction_(state, IoError_proto);
	return IOCLONE(proto);
}

/* ----------------------------------------------------------- */

IoSeq *IoError_newWithMessageFormat_(void *state, const char *format, ...)
{
	IoSymbol *message;
	
	va_list ap;
	va_start(ap, format);
	message = IoState_symbolWithUArray_copy_(state, UArray_newWithVargs_(format, ap), 0);
	va_end(ap);
	
	{
		IoError *error = IoError_new(state);
		IoObject_setSlot_to_(error, IoState_symbolWithCString_((IoState*)state, (char *)("message")), message);
		return error;
	}
}
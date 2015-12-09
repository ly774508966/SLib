#ifndef CHECKHEADER_SLIB_MEDIA_VIDEO_FORMAT
#define CHECKHEADER_SLIB_MEDIA_VIDEO_FORMAT

#include "definition.h"

#include "../graphics/color.h"
#include "../graphics/bitmap.h"

SLIB_MEDIA_NAMESPACE_BEGIN

class SLIB_EXPORT VideoFrame
{
public:
	BitmapData image;
};

SLIB_MEDIA_NAMESPACE_END

#endif
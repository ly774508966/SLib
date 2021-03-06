/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_MATH_DETAIL_INT128
#define CHECKHEADER_SLIB_MATH_DETAIL_INT128

#include "../int128.h"

namespace slib
{

	SLIB_INLINE Uint128& Uint128::operator=(const Uint128& other) = default;
	
	SLIB_INLINE const Uint128& Uint128::zero()
	{
		return *((Uint128*)((void*)_zero));
	}
	
	SLIB_INLINE void Uint128::setZero()
	{
		high = 0;
		low = 0;
	}
	
	SLIB_INLINE Uint128& Uint128::operator=(sl_uint64 num)
	{
		high = 0;
		low = num;
		return *this;
	}

}

#endif


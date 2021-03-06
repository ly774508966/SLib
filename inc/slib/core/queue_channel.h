/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_CORE_QUEUE_CHANNEL
#define CHECKHEADER_SLIB_CORE_QUEUE_CHANNEL

#include "definition.h"

#include "queue.h"
#include "array.h"

namespace slib
{

	template <class ITEM>
	class SLIB_EXPORT QueueChannelArray : public Object
	{
	public:
		struct Channel
		{
			AtomicLinkedList<ITEM> queue;
			Mutex locker;
		};

	protected:
		AtomicArray<Channel> m_arr;
		sl_size m_channelCurrent;

	public:
		QueueChannelArray();
	
		sl_size getChannelsCount();
	
		sl_bool setChannelsCount(sl_size n);

		sl_size getAllItemsCount() const;

		void removeAll();

		Link<ITEM>* pushBack(sl_size channelNo, const ITEM& value, sl_size countLimit = 0);

		sl_bool popBack(sl_size channelNo, ITEM* _out = sl_null);
	
		Link<ITEM>* pushFront(sl_size channelNo, const ITEM& value, sl_size countLimit = 0);

		sl_bool popFront(sl_size channelNo, ITEM* _out = sl_null);

		sl_bool popBack(ITEM* _out = sl_null);

		sl_bool popFront(ITEM* _out = sl_null);

	protected:
		LinkedList<ITEM> _getChannelQueue(sl_size no);

		LinkedList<ITEM> _activateChannelQueue(sl_size no);

	};

}

#include "detail/queue_channel.h"

#endif

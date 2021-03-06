/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "../../../inc/slib/render/opengl.h"

#if defined(SLIB_RENDER_SUPPORT_OPENGL_GLES)

#include "opengl_gles.h"

#include "../../../inc/slib/render/program.h"
#include "../../../inc/slib/core/queue.h"

#define _OPENGL_ES_IMPL
#define GL_BASE GLES
#define GL_ENGINE _GLES_Engine
#define GL_ENTRY(x) _GLES_ENTRY(x)
#include "opengl_impl.h"

#	if defined (SLIB_PLATFORM_IS_WIN32)

#include <Windows.h>

namespace slib
{
	_GLES_ENTRY_POINTS _GLES_ENTRIES;
	
#undef _SLIB_RENDER_GLES_ENTRY
#define _SLIB_RENDER_GLES_ENTRY(TYPE, name, ...) \
	proc = ::GetProcAddress(hDll, #name); \
	*((FARPROC*)(&(_GLES_ENTRIES.name))) = proc;
	
	static sl_bool _g_render_GLES_flagLoadedEntryPoints = sl_false;
	
	void GLES::loadEntries(const String& _pathDll, sl_bool flagReload)
	{
		String16 pathDll = _pathDll;
		if (pathDll.isEmpty()) {
			return;
		}
		if (!flagReload) {
			if (_g_render_GLES_flagLoadedEntryPoints) {
				return;
			}
		}
		HMODULE hDll = ::LoadLibraryW((LPCWSTR)(pathDll.getData()));
		if (!hDll) {
			//LogError("GLES", "Failed to load GLES dll - %s", pathDll);
			return;
		}
		FARPROC proc;
		_SLIB_RENDER_GLES_ENTRIES
		_g_render_GLES_flagLoadedEntryPoints = sl_true;
	}
	
	void GLES::loadEntries(sl_bool flagReload)
	{
		SLIB_STATIC_STRING16(s, "libGLESv2.dll");
		loadEntries(s, flagReload);
	}
	
	sl_bool GLES::isAvailable()
	{
		return _g_render_GLES_flagLoadedEntryPoints;
	}
}

#	else

namespace slib
{
	void GLES::loadEntries(const String& pathDll, sl_bool flagReload)
	{
	}
	
	void GLES::loadEntries(sl_bool flagReload)
	{
	}
	
	sl_bool GLES::isAvailable()
	{
		return sl_true;
	}
}

#	endif

#else

namespace slib
{
	Ref<GLRenderEngine> GLES::createEngine()
	{
		return sl_null;
	}
	
	void GLES::loadEntries(const String& pathDll, sl_bool flagReload)
	{
	}
	
	void GLES::loadEntries(sl_bool flagReload)
	{
	}
	
	sl_bool GLES::isAvailable()
	{
		return sl_false;
	}
}

#endif



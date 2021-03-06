/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_UI_EDIT_VIEW
#define CHECKHEADER_SLIB_UI_EDIT_VIEW

#include "definition.h"

#include "view.h"

namespace slib
{

	class EditView;
	
	class SLIB_EXPORT IEditViewListener
	{
	public:
		IEditViewListener();

		virtual ~IEditViewListener();

	public:
		virtual String onChange(EditView* edit, const String& newValue);
		
		virtual void onReturnKey(EditView* edit);
		
		virtual void onDoneEdit(EditView* edit);
		
	};
	
	class SLIB_EXPORT EditView : public View
	{
		SLIB_DECLARE_OBJECT
		
	public:
		EditView();

		~EditView();
		
	public:
		String getText();
		
		virtual void setText(const String& text, UIUpdateMode mode = UIUpdateMode::Redraw);
		
		Alignment getGravity();
		
		virtual void setGravity(Alignment align, UIUpdateMode mode = UIUpdateMode::Redraw);
		
		String getHintText();
		
		virtual void setHintText(const String& str, UIUpdateMode mode = UIUpdateMode::Redraw);
		
		sl_bool isReadOnly();
		
		virtual void setReadOnly(sl_bool flag, UIUpdateMode mode = UIUpdateMode::Redraw);
		
		virtual sl_bool isMultiLine();
		
		virtual void setMultiLine(sl_bool flag, UIUpdateMode mode = UIUpdateMode::Redraw);
		
		Color getTextColor();
		
		virtual void setTextColor(const Color& color, UIUpdateMode mode = UIUpdateMode::Redraw);
		
		Color getHintTextColor();
		
		virtual void setHintTextColor(const Color& color, UIUpdateMode mode = UIUpdateMode::Redraw);
		
		UIReturnKeyType getReturnKeyType();
		
		void setReturnKeyType(UIReturnKeyType type);
		
		UIKeyboardType getKeyboardType();
		
		void setKeyboardType(UIKeyboardType type);
		
		void setAutoCapitalizationType(UIAutoCapitalizationType type);
		
		UIAutoCapitalizationType getAutoCaptializationType();
		
		sl_bool isAutoDismissKeyboard();
		
		void setAutoDismissKeyboard(sl_bool flag);
		
	protected:
		// override
		void onMeasureLayout(sl_bool flagHorizontal, sl_bool flagVertical);
		
		// override
		void onDraw(Canvas* canvas);

		// override
		void onClick(UIEvent* ev);
		
	public:
		SLIB_PROPERTY(AtomicPtr<IEditViewListener>, Listener)
		
		SLIB_PROPERTY(AtomicFunction<String(EditView*, String)>, OnChange)
		
		SLIB_PROPERTY(AtomicFunction<void(EditView*)>, OnReturnKey)
		
		SLIB_PROPERTY(AtomicFunction<void(EditView*)>, OnDoneEdit)
		
	protected:
		virtual String onChange(const String& newValue);
		
		virtual void onReturnKey();
		
		virtual void onDoneEdit();
		
	public:
		// override
		Ref<ViewInstance> createNativeWidget(ViewInstance* parent);
		
		// override
		void dispatchKeyEvent(UIEvent* ev);
		
		virtual String dispatchChange(const String& newValue);
		
		virtual void dispatchReturnKey();
		
		virtual void dispatchDoneEdit();
		
	private:
		void _getText_NW();
		
		void _setText_NW(const String& text);
		
		void _setTextAlignment_NW(Alignment align);
		
		void _setHintText_NW(const String& str);
		
		void _setReadOnly_NW(sl_bool flag);
		
		void _setMultiLine_NW(sl_bool flag);
		
		void _setTextColor_NW(const Color& color);
		
		void _setHintTextColor_NW(const Color& color);
		
		void _setReturnKeyType_NW(UIReturnKeyType type);
		
		void _setKeyboardType_NW(UIKeyboardType type);
		
		void _setAutoCapitalizationType_NW(UIAutoCapitalizationType type);
		
		// override
		void _setFont_NW(const Ref<Font>& font);
		
		// override
		void _setBorder_NW(sl_bool flag);
		
		// override
		void _setBackgroundColor_NW(const Color& color);
		
		String _onChangeEditViewNative(EditView* ev, const String& text);
		
		void _onReturnKeyEditViewNative(EditView* ev);
		
		void _onDoneEditViewNative(EditView* ev);
		
	protected:
		AtomicString m_text;
		Alignment m_textAlignment;
		AtomicString m_hintText;
		sl_bool m_flagReadOnly;
		sl_bool m_flagMultiLine;
		Color m_textColor;
		Color m_hintTextColor;
		UIReturnKeyType m_returnKeyType;
		UIKeyboardType m_keyboardType;
		UIAutoCapitalizationType m_autoCapitalizationType;
		sl_bool m_flagAutoDismissKeyboard;
		
		Ref<Window> m_windowEdit;
		Ref<EditView> m_editViewNative;
		
	};
	
	class PasswordView : public EditView
	{
		SLIB_DECLARE_OBJECT
		
	public:
		PasswordView();
		
		~PasswordView();

	public:
		// override
		sl_bool isMultiLine();
		
		// override
		virtual void setMultiLine(sl_bool flag, UIUpdateMode mode = UIUpdateMode::Redraw);
		
	public:
		// override
		Ref<ViewInstance> createNativeWidget(ViewInstance* parent);
		
	};
	
	class TextArea : public EditView
	{
		SLIB_DECLARE_OBJECT
		
	public:
		TextArea();
		
		~TextArea();

	public:
		// override
		sl_bool isMultiLine();
		
		// override
		void setMultiLine(sl_bool flag, UIUpdateMode mode = UIUpdateMode::Redraw);
		
	public:
		// override
		Ref<ViewInstance> createNativeWidget(ViewInstance* parent);
		
	};

}

#endif

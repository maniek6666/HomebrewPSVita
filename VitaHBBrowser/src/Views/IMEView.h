#pragma once

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <sys/socket.h>
#include <psp2/ime_dialog.h>

#include "commonDialog.h"
#include "../singleton.h"
#include "View.h"
#include "activity.h"


struct IMEViewResult {
	CommonDialogStatus status = COMMON_DIALOG_STATUS_NONE;
	std::string userText = "";
};


class IMEView : Singleton<IMEView>, public View {
public:
	IMEView();
	static void openIMEView(std::shared_ptr<IMEViewResult> result, std::string title,
	                        SceUInt32 maxInputLength);
	static void openIMEView(std::shared_ptr<IMEViewResult> result, std::string title,
	                        std::string initialText = "", SceUInt32 maxInputLength = SCE_IME_DIALOG_MAX_TEXT_LENGTH);
	static void closeIMEView();
	~IMEView() override;

	int Display() override;

private:
	std::shared_ptr<IMEView> me_ptr;

	void prepare(std::shared_ptr<IMEViewResult> result, std::string title, std::string initialText,
	             SceUInt32 maxInputLength);

	std::basic_string<char16_t> _title;
	std::basic_string<char16_t> _initialText;
	SceUInt32 _maxTextLength;
	SceWChar16 *_input_text_buffer_utf16 = nullptr;
	std::string _input_text_buffer_utf8;
	CommonDialogStatus _status = COMMON_DIALOG_STATUS_NONE;
	std::shared_ptr<IMEViewResult> _result;
	bool shown_dialog = false;
};

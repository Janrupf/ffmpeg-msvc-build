#pragma once

#include <iostream>
#include <memory>

#include "../avcodec/codec.h"

extern "C" {
#define __STDC_CONSTANT_MACROS
#include <libavformat/avformat.h>
}

struct AVFormatContextDeleter {
	void operator()(AVFormatContext* context) const {
		avformat_close_input(&context);
	};
};

using AVFormatContextPtr = std::unique_ptr<AVFormatContext, AVFormatContextDeleter>;

AVFormatContextPtr open_input(const std::string& url) {
	AVFormatContext* context{ nullptr };
	auto ret{ avformat_open_input(&context, url.c_str(), nullptr, nullptr) };
	if (ret < 0) {
		std::cerr << "failed to allocate output context for " << url << ": " << av_error_string(ret) << std::endl;
	}
	else if (!context) {
		std::cerr << "failed to allocate output context for " << url << std::endl;
	}
	else {
		auto ret2{ avformat_find_stream_info(context, 0) };
		if (ret2 < 0) {
			std::cerr << "failed to retrieve input stream information for " << url << ": " << av_error_string(ret) << std::endl;
			avformat_close_input(&context);
			context = nullptr;
		}
	}
	return AVFormatContextPtr{ context };
}
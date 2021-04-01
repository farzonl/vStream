#ifndef ENCODER_H
#define ENCODER_H

#ifdef __cplusplus

#define __STDC_CONSTANT_MACROS
#ifdef _STDINT_H
#undef _STDINT_H
#endif

#include <stdint.h>
extern "C" {
#endif

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavutil/opt.h> //av_opt_set_int and others for audio
#include <libswresample/swresample.h>
#include <libswscale/swscale.h> //sws_scale, SWS_BICUBIC

#ifdef __cplusplus
} // extern "C"
#endif

#include "pch.h"

class Encoder {
private:
  void init(AVFormatContext *pContext, AVStream *pStream);

protected:
  AVFrame *m_pFrameOut;
  AVStream *m_pStream;
  AVFormatContext *m_pContext;

public:
  Encoder();
  virtual ~Encoder();
  virtual int open(AVFormatContext *pContext, AVCodec *pCodec,
                   AVStream *pStream);
  void close();
};

#endif // ENCODER_H
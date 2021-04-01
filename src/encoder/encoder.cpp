#include "encoder.h"

Encoder::Encoder()
    : m_pFrameOut(nullptr), m_pStream(nullptr), m_pContext(nullptr) {
  m_pFrameOut = av_frame_alloc();
}

Encoder::~Encoder() { av_frame_free(&m_pFrameOut); }

void Encoder::close() { avcodec_close(m_pStream->codec); }

void Encoder::init(AVFormatContext *pContext, AVStream *pStream) {
  this->m_pContext = pContext;
  this->m_pStream = pStream;
}

int Encoder::open(AVFormatContext *pContext, AVCodec *pCodec,
                  AVStream *pStream) {
  init(pContext, pStream);
  AVCodecContext *c = pStream->codec;
  int ret = avcodec_open2(c, pCodec, nullptr);
  if (ret < 0) {
    std::cout << "Could not open codec: " << ret << std::endl;
    exit(1);
  }
  return ret;
}
#ifndef AUDIO_ENCODER_H
#define AUDIO_ENCODER_H

#include "encoder.h"

struct pnts {
  int64_t pts, dts;
  pnts(int64_t pts, int64_t dts) : pts(pts), dts(dts) {}
};

class AudioEncoder : public Encoder {
private:
  size_t audio_in_frame_sz;
  std::queue<pnts> timeStamps;

public:
  AudioEncoder();
  virtual ~AudioEncoder() {}
  virtual int open(AVFormatContext *pContext, AVCodec *pCodec,
                   AVStream *pStream) override;
  void write(const std::vector<uint8_t> &bitStream);
};
#endif // AUDIO_ENCODER_H
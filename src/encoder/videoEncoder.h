#ifndef VIDEO_ENCODER_H
#define VIDEO_ENCODER_H

#include "encoder.h"

enum class FrameType {
  // (Intra-coded picture) is a complete image
  IFrame,
  // Predicted picture) holds only the changes in the image from the previous
  // frame
  PFrame,
  //(Bidirectional predicted picture) differences between the current frame and
  // both the preceding and following frames
  BFrame
};

class VideoEncoder : public Encoder {

public:
  VideoEncoder();
  virtual ~VideoEncoder() {}
  void write(const std::vector<uint8_t> &bitStream, FrameType fType);
};

#endif // VIDEO_ENCODER_H
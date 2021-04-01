#ifndef MUXER_H
#define MUXER_H

#include "encoder/videoEncoder.h"
#include "encoder/audioEncoder.h"

class Muxer {
    VideoEncoder vWriter;
    AudioEncoder aWriter;
    int videoBitRate, audioBitRate;
    AVFormatContext *m_pContext;
public:
    Muxer();
};
#endif // MUXER_H
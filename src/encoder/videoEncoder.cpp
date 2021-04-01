#include "videoEncoder.h"

VideoEncoder::VideoEncoder() : Encoder() {}

void VideoEncoder::write(const std::vector<uint8_t> &bitStream,
                         FrameType fType) {

  if (m_pContext == nullptr || m_pStream == NULL) {
    return;
  }

  AVPacket pkt = {0};
  av_init_packet(&pkt);

  pkt.stream_index = m_pStream->index;
  pkt.data = const_cast<uint8_t *>(bitStream.data());
  pkt.size = bitStream.size();

  if (fType == FrameType::IFrame) {
    pkt.flags |= AV_PKT_FLAG_KEY;
  }

  pkt.pts =
      av_rescale_q(pkt.pts, m_pStream->codec->time_base, m_pStream->time_base);
  pkt.dts =
      av_rescale_q(pkt.dts, m_pStream->codec->time_base, m_pStream->time_base);

  if (av_interleaved_write_frame(m_pContext, &pkt)) {
    std::cout << "FFMPEG: Error while writing video frame" << std::endl;
    exit(1);
  }
  av_free_packet(&pkt);
}

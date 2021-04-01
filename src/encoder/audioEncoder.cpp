#include "audioEncoder.h"
AudioEncoder::AudioEncoder() : Encoder(), audio_in_frame_sz(0) {}

int AudioEncoder::open(AVFormatContext *pContext, AVCodec *pCodec,
                       AVStream *pStream) {
  int ret = Encoder::open(pContext, pCodec, pStream);
  AVCodecContext *c = pStream->codec;
  if (c->codec->capabilities & AV_CODEC_CAP_VARIABLE_FRAME_SIZE) {
    audio_in_frame_sz = 10000;
  } else {
    audio_in_frame_sz = c->frame_size;
  }
  return ret;
}

// uint8_t *audio_src_data, int a_bufsize
void AudioEncoder::write(const std::vector<uint8_t> &bitStream) {
  if (m_pContext == nullptr || m_pStream == NULL) {
    return;
  }

  AVPacket pkt = {0}; // data and size must be 0;
  int cur_pkt;
  AVCodecContext *c = m_pStream->codec;
  m_pFrameOut->nb_samples = audio_in_frame_sz;
  int buf_size =
      bitStream.size() * av_get_bytes_per_sample(c->sample_fmt) * c->channels;
  uint8_t *a_src_cntr = const_cast<uint8_t *>(bitStream.data());
  for (int i = 0; i < bitStream.size(); i += 4 * audio_in_frame_sz) {
    av_init_packet(&pkt);
    avcodec_fill_audio_frame(m_pFrameOut, c->channels, c->sample_fmt,
                             a_src_cntr, buf_size, 1);

    avcodec_encode_audio2(c, &pkt, m_pFrameOut, &cur_pkt);

    if (cur_pkt) {
      if (pkt.pts != AV_NOPTS_VALUE)
        pkt.pts = av_rescale_q(pkt.pts, m_pStream->codec->time_base,
                               m_pStream->time_base);

      if (pkt.dts != AV_NOPTS_VALUE)
        pkt.dts = av_rescale_q(pkt.dts, m_pStream->codec->time_base,
                               m_pStream->time_base);

      pkt.stream_index = m_pStream->index;
      pkt.flags |= AV_PKT_FLAG_KEY;

      // Write the compressed frame to the media file.
      try {
        if (av_interleaved_write_frame(m_pContext, &pkt) != 0) {
          fprintf(stderr, "Error while writing audio frame\n");
          exit(1);
        }
      } catch (std::exception &e) {
        std::cout << "An exception occurred. Exception Nr. " << e.what()
                  << std::endl;
      }
    }

    a_src_cntr += 4 * audio_in_frame_sz;
    timeStamps.push(pnts(pkt.pts, pkt.dts));
    av_free_packet(&pkt);
  }
}
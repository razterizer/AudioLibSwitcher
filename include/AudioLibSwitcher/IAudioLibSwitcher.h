//
//  IAudioLibSwitcher.h
//  AudioLibSwitcher
//
//  Created by Rasmus Anthin on 2024-03-24.
//

#pragma once
#include <string>


namespace audio
{
  
  struct IAudioLibSwitcher
  {
    virtual ~IAudioLibSwitcher() = default;
  
    virtual void init() = 0;
    
    virtual void finish() = 0;
  
    virtual unsigned int create_source() = 0;
    
    virtual void destroy_source(unsigned int src_id) = 0;
    
    virtual unsigned int create_buffer() = 0;
    
    virtual void destroy_buffer(unsigned int buf_id) = 0;
    
    virtual void play_source(unsigned int src_id) = 0;
    
    virtual bool is_source_playing(unsigned int src_id) = 0;
    
    virtual void pause_source(unsigned int src_id) = 0;
    
    virtual void stop_source(unsigned int src_id) = 0;
    
    virtual void set_source_volume(unsigned int src_id, float vol) = 0;
    
    virtual void set_source_pitch(unsigned int src_id, float pitch) = 0;
    
    virtual void set_source_looping(unsigned int src_id, bool loop) = 0;
    
    virtual void set_source_standard_params(unsigned int src_id) = 0;
    
    virtual bool set_buffer_data_8u(unsigned int buf_id, const std::vector<unsigned char>& buffer, int num_channels, int sample_rate) = 0;
    
    virtual bool set_buffer_data_16s(unsigned int buf_id, const std::vector<signed short>& buffer, int num_channels, int sample_rate) = 0;
    
    virtual bool set_buffer_data_32f(unsigned int buf_id, const std::vector<float>& buffer, int num_channels, int sample_rate) = 0;
    
    virtual void attach_buffer_to_source(unsigned int src_id, unsigned int buf_id) = 0;

    virtual void detach_buffer_from_source(unsigned int src_id) = 0;
    
    virtual std::string check_error() = 0;
  };
  
}

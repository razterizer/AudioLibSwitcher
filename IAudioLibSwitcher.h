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
  
    virtual int create_source() = 0;
    
    virtual void destroy_source(int src_id) = 0;
    
    virtual int create_buffer() = 0;
    
    virtual void destroy_buffer(int buf_id) = 0;
    
    virtual void play_source(int src_id) = 0;
    
    virtual bool is_source_playing(int src_id) = 0;
    
    virtual void pause_source(int src_id) = 0;
    
    virtual void stop_source(int src_id) = 0;
    
    virtual void set_source_volume(int src_id, float vol) = 0;
    
    virtual void set_source_pitch(int src_id, float pitch) = 0;
    
    virtual void set_source_looping(int src_id, bool loop) = 0;
    
    // #NOTE: Might be deprecated.
    virtual void detach_source(int src_id) = 0;
    
    virtual void set_source_standard_params(int src_id) = 0;
    
    virtual void set_buffer_data_mono_16(int buf_id, const std::vector<short>& buffer, int sample_rate) = 0;
    
    virtual void attach_buffer_to_source(int src_id, int buf_id) = 0;
    
    virtual std::string check_error() = 0;
  };
  
}

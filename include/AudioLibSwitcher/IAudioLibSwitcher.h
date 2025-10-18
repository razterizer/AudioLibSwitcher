//
//  IAudioLibSwitcher.h
//  AudioLibSwitcher
//
//  Created by Rasmus Anthin on 2024-03-24.
//

#pragma once
#include <string>
#include <array>
#include <optional>


namespace audio
{
  
  struct IAudioLibSwitcher
  {
    virtual ~IAudioLibSwitcher() = default;
  
    virtual void init(bool enable_audio = true) = 0;
    
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
    
    virtual void set_source_panning(unsigned int src_id, std::optional<float> pan = std::nullopt) = 0;
    
    virtual void init_3d_scene() = 0;

    virtual void enable_source_3d_audio(unsigned int src_id, bool enable) = 0;

    // std::array<float, 9> is a row-major 3x3 matrix.
    virtual bool set_source_3d_state_channel(
        unsigned int src_id, int channel,
        const std::array<float, 9>& rot_mtx,
        const std::array<float, 3>& pos_world, const std::array<float, 3>& vel_world) = 0;

    // std::array<float, 9> is a row-major 3x3 matrix.
    virtual bool set_listener_3d_state_channel(
        int channel,
        const std::array<float, 9>& rot_mtx,
        const std::array<float, 3>& pos_world, const std::array<float, 3>& vel_world) = 0;

    virtual bool set_source_speed_of_sound(unsigned int src_id, float speed_of_sound) = 0;
    virtual std::optional<float> get_source_speed_of_sound(unsigned int src_id) = 0;

    virtual bool set_source_attenuation_min_distance(unsigned int src_id, float min_dist) = 0;
    virtual bool set_source_attenuation_max_distance(unsigned int src_id, float max_dist) = 0;
    virtual bool set_source_attenuation_constant_falloff(unsigned int src_id, float const_falloff) = 0;
    virtual bool set_source_attenuation_linear_falloff(unsigned int src_id, float lin_falloff) = 0;
    virtual bool set_source_attenuation_quadratic_falloff(unsigned int src_id, float sq_falloff) = 0;
    
    // directivity_alpha = 0 : Omni.
    // directivity_alpha = 1 : Fully Directional.
    // [0, 1].
    virtual bool set_source_directivity_alpha(unsigned int src_id, float directivity_alpha) = 0;
    
    // [1, 8]. 8 = sharpest.
    virtual bool set_source_directivity_sharpness(unsigned int src_id, float directivity_sharpness) = 0;
    
    // Cardioid, SuperCardioid, HalfRectifiedDipole, Dipole.
    virtual bool set_source_directivity_type(unsigned int src_id, DirectivityType directivity_type) = 0;
    
    // [0.f, 1.f]. 0 = Silence, 1 = No Attenuation.
    virtual bool set_source_rear_attenuation(unsigned int src_id, float rear_attenuation) = 0;
    
    // [0.f, 1.f]. 0 = Silence, 1 = No Attenuation.
    virtual bool set_listener_rear_attenuation(float rear_attenuation) = 0;
    
    virtual std::string check_error() = 0;
  };
  
}

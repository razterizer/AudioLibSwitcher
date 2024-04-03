# AudioLibSwitcher

The purpose of this repository is to be an interface-based layer between different audio libraries so that you can easily switch between different audio libs.

The reason for such a solution is because different libs come under different licenses and you might realize that you one library doesn't suit your project because of license mismatch. This interface will allow you to then easily unplug-plug-and-play and use the library that best work for you without having to rewrite a lot of code in your project.

## API

  
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
    
    // #NOTE: Might be deprecated.
    virtual void detach_source(unsigned int src_id) = 0;
    
    virtual void set_source_standard_params(unsigned int src_id) = 0;
    
    virtual void set_buffer_data_mono_16(unsigned int buf_id, const std::vector<short>& buffer, int sample_rate) = 0;
    
    virtual void attach_buffer_to_source(unsigned int src_id, unsigned int buf_id) = 0;
    
    virtual std::string check_error() = 0;
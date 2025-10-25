# AudioLibSwitcher

![GitHub License](https://img.shields.io/github/license/razterizer/AudioLibSwitcher?color=blue)
![Static Badge](https://img.shields.io/badge/linkage-header_only-yellow)
![Static Badge](https://img.shields.io/badge/C%2B%2B-20-yellow)

The purpose of this repository is to be an interface-based layer between different audio libraries so that you can easily switch between different audio libs.

The reason for such a solution is because different libs come under different licenses and you might realize that you one library doesn't suit your project because of license mismatch. This interface will allow you to then easily unplug-plug-and-play and use the library that best work for you without having to rewrite a lot of code in your project.

The API is OpenAL-esque so that people who are used to OpenAL should be comfortable with this API.
Note that this is just a first iteration of the API and once I'm done with the `libsoundio` adapter, I will probably add more functions.

## API
```cpp
  
    virtual void init(bool enable_audio = true) = 0;
    
    virtual void finish() = 0;
  
    virtual unsigned int create_source() = 0;
    
    virtual void destroy_source(unsigned int src_id) = 0;
    
    virtual unsigned int create_buffer() = 0;
    
    virtual void destroy_buffer(unsigned int buf_id) = 0;
    
    virtual void play_source(unsigned int src_id) = 0;
    
    virtual std::optional<bool> is_source_playing(unsigned int src_id) = 0;
    
    virtual void pause_source(unsigned int src_id) = 0;
    
    virtual std::optional<bool> is_source_paused(unsigned int src_id) const = 0;
        
    virtual void stop_source(unsigned int src_id) = 0;
    
    virtual void set_source_volume(unsigned int src_id, float vol) = 0;
    
    virtual std::optional<float> get_source_volume(unsigned int src_id) const = 0;
    
    virtual void set_source_pitch(unsigned int src_id, float pitch) = 0;
    
    virtual std::optional<float> get_source_pitch(unsigned int src_id) const = 0;
    
    virtual void set_source_looping(unsigned int src_id, bool loop) = 0;
    
    virtual std::optional<bool> get_source_looping(unsigned int src_id) const
    
    virtual void set_source_standard_params(unsigned int src_id) = 0;
    
    virtual bool set_buffer_data_8u(unsigned int buf_id, const std::vector<unsigned char>& buffer, int num_channels, int sample_rate) = 0;
    
    virtual bool set_buffer_data_16s(unsigned int buf_id, const std::vector<signed short>& buffer, int num_channels, int sample_rate) = 0;
    
    virtual bool set_buffer_data_32f(unsigned int buf_id, const std::vector<float>& buffer, int num_channels, int sample_rate) = 0;
    
    virtual void attach_buffer_to_source(unsigned int src_id, unsigned int buf_id) = 0;

    virtual void detach_buffer_from_source(unsigned int src_id) = 0;
    
    virtual void set_source_panning(unsigned int src_id, std::optional<float> pan = std::nullopt) = 0;
    
    std::optional<float> get_source_panning(unsigned int src_id) const = 0;
    
    virtual void init_3d_scene() = 0;

    virtual void enable_source_3d_audio(unsigned int src_id, bool enable) = 0;

    // std::array<float, 9> is a row-major 3x3 matrix.
    virtual bool set_source_3d_state_channel(
        unsigned int src_id, int channel,
        const std::array<float, 9>& rot_mtx,
        const std::array<float, 3>& pos_world, const std::array<float, 3>& vel_world) = 0;
        
    // std::array<float, 9> is a row-major 3x3 matrix.
    virtual bool get_source_3d_state_channel(unsigned int src_id, int channel,
        std::array<float, 9>& rot_mtx,
        std::array<float, 3>& pos_world, std::array<float, 3>& vel_world) const = 0;

    // std::array<float, 9> is a row-major 3x3 matrix.
    virtual bool set_listener_3d_state_channel(
        int channel,
        const std::array<float, 9>& rot_mtx,
        const std::array<float, 3>& pos_world, const std::array<float, 3>& vel_world) = 0;
        
    // std::array<float, 9> is a row-major 3x3 matrix.
    virtual bool get_listener_3d_state_channel(int channel,
        std::array<float, 9>& rot_mtx,
        std::array<float, 3>& pos_world, std::array<float, 3>& vel_world) const = 0;

    virtual bool set_source_speed_of_sound(unsigned int src_id, float speed_of_sound) = 0;
    virtual std::optional<float> get_source_speed_of_sound(unsigned int src_id) = 0;

    virtual bool set_source_attenuation_min_distance(unsigned int src_id, float min_dist) = 0;
    virtual std::optional<float> get_source_attenuation_min_distance(unsigned int src_id) const = 0;
    
    virtual bool set_source_attenuation_max_distance(unsigned int src_id, float max_dist) = 0;
    virtual std::optional<float> get_source_attenuation_max_distance(unsigned int src_id) const = 0;
    
    virtual bool set_source_attenuation_constant_falloff(unsigned int src_id, float const_falloff) = 0;
    virtual std::optional<float> get_source_attenuation_constant_falloff(unsigned int src_id) const = 0;
    
    virtual bool set_source_attenuation_linear_falloff(unsigned int src_id, float lin_falloff) = 0;
    virtual std::optional<float> get_source_attenuation_linear_falloff(unsigned int src_id) const = 0;
    
    virtual bool set_source_attenuation_quadratic_falloff(unsigned int src_id, float sq_falloff) = 0;
    virtual std::optional<float> get_source_attenuation_quadratic_falloff(unsigned int src_id) const = 0;
    
    // directivity_alpha = 0 : Omni.
    // directivity_alpha = 1 : Fully Directional.
    // [0, 1].
    virtual bool set_source_directivity_alpha(unsigned int src_id, float directivity_alpha) = 0;
    
    // directivity_alpha = 0 : Omni.
    // directivity_alpha = 1 : Fully Directional.
    // [0, 1].
    virtual std::optional<float> get_source_directivity_alpha(unsigned int src_id) const = 0;
    
    // [1, 8]. 8 = sharpest.
    virtual bool set_source_directivity_sharpness(unsigned int src_id, float directivity_sharpness) = 0;
    
    // [1, 8]. 8 = sharpest.
    virtual std::optional<float> get_source_directivity_sharpness(unsigned int src_id) const = 0;
    
    // 0 = Cardioid, 1 = SuperCardioid, 2 = HalfRectifiedDipole, 3 = Dipole.
    virtual bool set_source_directivity_type(unsigned int src_id, int directivity_type) = 0;
    
    // 0 = Cardioid, 1 = SuperCardioid, 2 = HalfRectifiedDipole, 3 = Dipole.
    virtual std::optional<int> get_source_directivity_type(unsigned int src_id) const = 0;
    
    // [0.f, 1.f]. 0 = Silence, 1 = No Attenuation.
    virtual bool set_source_rear_attenuation(unsigned int src_id, float rear_attenuation) = 0;
    
    // [0.f, 1.f]. 0 = Silence, 1 = No Attenuation.
    virtual std::optional<float> get_source_rear_attenuation(unsigned int src_id) const = 0;
    
    // [0.f, 1.f]. 0 = Silence, 1 = No Attenuation.
    virtual bool set_listener_rear_attenuation(float rear_attenuation) = 0;
    
    // [0.f, 1.f]. 0 = Silence, 1 = No Attenuation.
    virtual std::optional<float> get_listener_rear_attenuation() const = 0;
    
    // 0 = RH_XRight_YUp_ZBackward, 1 = RH_XLeft_YUp_ZForward, 2 = RH_XRight_YDown_ZForward, 3 = RH_XLeft_YDown_ZBackward, 4 = RH_XRight_YForward_ZUp.
    virtual bool set_source_coordsys_convention(unsigned int src_id, int cs_conv) = 0;
    
    // 0 = RH_XRight_YUp_ZBackward, 1 = RH_XLeft_YUp_ZForward, 2 = RH_XRight_YDown_ZForward, 3 = RH_XLeft_YDown_ZBackward, 4 = RH_XRight_YForward_ZUp.
    virtual std::optional<int> get_source_coordsys_convention(unsigned int src_id) const = 0;
    
    // 0 = RH_XRight_YUp_ZBackward, 1 = RH_XLeft_YUp_ZForward, 2 = RH_XRight_YDown_ZForward, 3 = RH_XLeft_YDown_ZBackward, 4 = RH_XRight_YForward_ZUp.
    virtual bool set_listener_coordsys_convention(int cs_conv) = 0;
    
    // 0 = RH_XRight_YUp_ZBackward, 1 = RH_XLeft_YUp_ZForward, 2 = RH_XRight_YDown_ZForward, 3 = RH_XLeft_YDown_ZBackward, 4 = RH_XRight_YForward_ZUp.
    virtual std::optional<int> get_listener_coordsys_convention() const = 0;
    
    virtual std::string check_error() = 0;
```

## AudioLibSwitcher : Switching from OpenAL Soft to applaudio for your program

This documentation here can be found in [`8Beat`](https://github.com/razterizer/8Beat) as well.

This section describes how to change your application code to work with either `applaudio` or `OpenAL Soft`.

As my own audio library [`applaudio`](https://github.com/razterizer/applaudio) is becoming more and more stable, you have the option to choose between OpenAL/OpenAL_Soft (GPL-based) and applaudio (MIT). This is nice, because it will allow you to build a release that is entirely MIT-licensed without having to be infected by the GPL-virus.

### Dependencies

The `dependencies` file of your application repo can now look like this:
```
lib/Core                       https://github.com/razterizer/Core.git                   dbe2f701a255d578308c254839a3641786777658
lib/Termin8or                  https://github.com/razterizer/Termin8or.git              fb8e4ce8efabe83167192c5d82c4448e6ec8b45f
lib/8Beat                      https://github.com/razterizer/8Beat                      041761531cdc6721d4aea07da63c0b2a5b7403d7
lib/AudioLibSwitcher_applaudio https://github.com/razterizer/AudioLibSwitcher_applaudio db2648c00533a8894339095b0e727989e3ae7425
# lib/AudioLibSwitcher_OpenAL    https://github.com/razterizer/AudioLibSwitcher_OpenAL    811c60c23a446d5f2894e9379c938df19f889c41
lib/TrainOfThought             https://github.com/razterizer/TrainOfThought             fe8a5f0fd7e492bb1e8dfffac9aef1ee888735da
lib/applaudio                  https://github.com/razterizer/applaudio                  702d425e551f19717baed605ae7983ceddb1587b
# lib/3rdparty_OpenAL            https://github.com/razterizer/3rdparty_OpenAL            d8361648d7b505154109f1ba074922555a96e5de                    win
```
This way you'll using locked and stable versions of each library. Things relating to `OpenAL` is now commented out here.

So, key takeaways here are:

* `OpenAL` (`OpenAL_Soft`) : Use https://github.com/razterizer/AudioLibSwitcher_OpenAL and https://github.com/razterizer/3rdparty_OpenAL.
* `applaudio` : Use https://github.com/razterizer/AudioLibSwitcher_applaudio and https://github.com/razterizer/applaudio.

### XCode Project

On Mac in the XCode project you can now choose `OpenAL` if you still want to use that:
<img width="1089" height="441" alt="image" src="https://github.com/user-attachments/assets/7f62fc4a-8575-440b-8a47-e2163543c1a1" />

or use `AudioToolbox`, `CoreAudio` and `CoreFoundation` if you want to use `applaudio` instead:
<img width="1074" height="409" alt="image" src="https://github.com/user-attachments/assets/b409d98d-dded-477c-88a9-58b789b4501e" />

In your XCode project you may have the following search paths. For example:
<img width="935" height="343" alt="image" src="https://github.com/user-attachments/assets/92b9bcae-4164-4312-ae38-a9c645e2b423" />

If using `OpenAL` then you can keep `../lib/AudioLibSwitcher_OpenAL/include/` and `/opt/homebrew/opt/openal-soft/include/`, but if you use `applaudio` you can just keep `../lib/AudioLibSwitcher_applaudio/include/` and `../lib/applaudio/include/` instead.

You also need to define `USE_APPLAUDIO` for both the `Release` and the `Debug` targets. Like this:
<img width="620" height="129" alt="image" src="https://github.com/user-attachments/assets/78df78b6-1952-434a-8303-d2defceeb08f" />


### Build Script

Then your build script for MacOS (CoreAudio) and Linux (here Debian-based) (ALSA) would be something like:
```bash
#!/bin/bash

os_name=$(uname)

if [[ $os_name == *"Darwin"* ]]; then
  additional_flags="\
    -I../../lib/Core/include \
    -I../../lib/Termin8or/include \
    -I../../lib/8Beat/include \
    -I../../lib/TrainOfThought/include \
    -I../../lib/AudioLibSwitcher_applaudio/include \
    -I../../lib/applaudio/include -framework AudioToolbox -framework CoreAudio -framework CoreFoundation -DUSE_APPLAUDIO"
  # -I../../lib/AudioLibSwitcher_OpenAL/include \
  # -I/opt/homebrew/opt/openal-soft/include -L/opt/homebrew/opt/openal-soft/lib -lopenal"
else
  additional_flags="\
    -I../../lib/Core/include \
    -I../../lib/Termin8or/include \
    -I../../lib/8Beat/include \
    -I../../lib/TrainOfThought/include \
    -I../../lib/AudioLibSwitcher_applaudio/include \
    -I../../lib/applaudio/include -DUSE_APPLAUDIO"
  # -I../../lib/AudioLibSwitcher_OpenAL/include"
  #export BUILD_PKG_CONFIG_MODULES='openal'
  export BUILD_PKG_CONFIG_MODULES='alsa'
fi

../../lib/Core/build.sh asciiroids "$1" "${additional_flags[@]}"

# Capture the exit code of Core/build.sh
exit_code=$?

if [ $exit_code -ne 0 ]; then
  echo "Core/build.sh failed with exit code $exit_code"
  exit $exit_code
fi

### Post-Build Actions ###

mkdir -p bin/fonts/
cp ../../lib/Termin8or/include/Termin8or/title/fonts/* bin/fonts/

cp music.ct bin/
```

For MacOS, the important bits above are those concerning `AudioLibSwitcher_applaudio`, `applaudio`, `-framework AudioToolbox`, `-framework CoreAudio`, `-framework CoreFoundation` and `-DUSE_APPLAUDIO`.

For Linux, the important bits above are those concerning `AudioLibSwitcher_applaudio`, `applaudio`, `-DUSE_APPLAUDIO` and `export BUILD_PKG_CONFIG_MODULES='alsa'`.

### Windows vcxproj Changes

Then finally for the Windows build you need to change the external include paths from this (OpenAL-based):

```xml
<ExternalIncludePath>$(SolutionDir)\..\..\lib\Core\include;$(SolutionDir)\..\..\lib\Termin8or\include;$(SolutionDir)\..\..\lib\8Beat\include;$(SolutionDir)\..\..\lib\TrainOfThought\include;$(SolutionDir)\..\..\lib\AudioLibSwitcher_OpenAL\include;$(SolutionDir)\..\..\lib\3rdparty_OpenAL\include</ExternalIncludePath>
```

to this (applaudio-based)

```xml
<ExternalIncludePath>$(SolutionDir)\..\..\lib\Core\include;$(SolutionDir)\..\..\lib\Termin8or\include;$(SolutionDir)\..\..\lib\8Beat\include;$(SolutionDir)\..\..\lib\TrainOfThought\include;$(SolutionDir)\..\..\lib\AudioLibSwitcher_applaudio\include;$(SolutionDir)\..\..\lib\applaudio\include</ExternalIncludePath>
```

You also need to change the linkage from this (OpenAL-based):

```xml
<AdditionalDependencies>openal32.lib;%(AdditionalDependencies)</AdditionalDependencies>
<AdditionalLibraryDirectories>$(SolutionDir)\..\..\lib\3rdparty_OpenAL\lib;%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
```

to this (applaudio-based):

```xml
<AdditionalDependencies>ole32.lib;%(AdditionalDependencies)</AdditionalDependencies>
```

And remove the copying of the OpenAL dll:

```xml
<PostBuildEvent>
      <Command>xcopy "$(SolutionDir)\music.ct" "$(TargetDir)" /Y
xcopy "$(SolutionDir)\..\..\lib\Termin8or\include\Termin8or\title\fonts\*" "$(TargetDir)\fonts\" /Y
xcopy "$(SolutionDir)..\..\lib\3rdparty_OpenAL\lib\OpenAL32.dll" "$(TargetDir)" /Y</Command>
    </PostBuildEvent>
```

so it becomes:

```xml
<PostBuildEvent>
      <Command>xcopy "$(SolutionDir)\music.ct" "$(TargetDir)" /Y
xcopy "$(SolutionDir)\..\..\lib\Termin8or\include\Termin8or\title\fonts\*" "$(TargetDir)\fonts\" /Y
    </PostBuildEvent>
```

Also to signal to the `8Beat/AudioSourceHandler.h` that you want to use the applaudio lib rather than OpenAL lib, then you need to add the `USE_APPLAUDIO` define:

```xml
<PreprocessorDefinitions>WIN32;_DEBUG;_CONSOLE;NOMINMAX;USE_APPLAUDIO;%(PreprocessorDefinitions)</PreprocessorDefinitions>
```

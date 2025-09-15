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
```

## Switching from OpenAL to applaudio

The same documentation can be found also in the 8Beat/README.md file.

As my own audio library [`applaudio`](https://github.com/razterizer/applaudio) is becoming more and more stable, you have the option to choose between OpenAL/OpenAL_Soft (GPL-based) and applaudio (MIT). This is nice, because it will allow you to build a release that is entirely MIT-licensed without having to be infected by the GPL-virus.

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

On Mac in the XCode project you can now choose `OpenAL` if you still want to use that:
<img width="1089" height="441" alt="image" src="https://github.com/user-attachments/assets/7f62fc4a-8575-440b-8a47-e2163543c1a1" />

or use `AudioToolbox`, `CoreAudio` and `CoreFoundation` if you want to use `applaudio` instead:
<img width="1074" height="409" alt="image" src="https://github.com/user-attachments/assets/b409d98d-dded-477c-88a9-58b789b4501e" />

In your XCode project you may have the following search paths. For example:
<img width="935" height="343" alt="image" src="https://github.com/user-attachments/assets/92b9bcae-4164-4312-ae38-a9c645e2b423" />

If using `OpenAL` then you can keep `../lib/AudioLibSwitcher_OpenAL/include/` and `/opt/homebrew/opt/openal-soft/include/`, but if you use `applaudio` you can just keep `../lib/AudioLibSwitcher_applaudio/include/` and `../lib/applaudio/include/` instead.

Then your build script for MacOS (CoreAudio) and Linux (ALSA) would be something like:
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
    -I../../lib/applaudio/include -framework AudioToolbox -framework CoreAudio -framework CoreFoundation"
  # -I../../lib/AudioLibSwitcher_OpenAL/include \
  # -I/opt/homebrew/opt/openal-soft/include -L/opt/homebrew/opt/openal-soft/lib -lopenal"
else
  additional_flags="\
    -I../../lib/Core/include \
    -I../../lib/Termin8or/include \
    -I../../lib/8Beat/include \
    -I../../lib/TrainOfThought/include \
    -I../../lib/AudioLibSwitcher_applaudio/include \
    -I../../lib/applaudio/include"
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

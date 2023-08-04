#include "voice.h"

VoiceClass *voice_instances;

void VoiceClass::init(){
  voice_instances = this;
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(21); //Volume min = 0, max = 21
}

void VoiceClass::change_volume(uint8_t volume){
  audio.setVolume(volume);
}

void VoiceClass::speak(const char *buff){
  audio.connecttospeech(buff, "en");                      //Mengubah data digital suara ke analog
  neopixelWrite(RGB_BUILTIN,0,0,RGB_BRIGHTNESS); // Blue
  bool soundPlay = true;
  debugVal(AUDIO_TAG,"Audio out : ",buff);

  while(soundPlay){
    audio.loop();
    if(!audio.isRunning()) {
      soundPlay = false;
      debug(AUDIO_TAG, "Audio Stopped");
      neopixelWrite(RGB_BUILTIN,0,0,0); // Blue
    }
  }
}

VoiceClass voice;
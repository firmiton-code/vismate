#include "vismate.h"

VisMateClass *vismate_instances;

VisMateClass::VisMateClass(){
    vismate_instances = this;
}

void VisMateClass::init_tof(){
    
}

void VisMateClass::setup_control(){
    pinMode(_button_pin, INPUT_PULLUP);
}

void VisMateClass::init_connection(){
    net.begin();
    lcd.setBuff(data.read("ssid"));
    debugVal(VIS_TAG, "Connected at ", net.get_ip());
}

void VisMateClass::init_lcd(){
    lcd.init_tft();
    lcd.show_logo();
}

void VisMateClass::speaker_test(){
    voice.init();
    voice.change_volume(21);
    voice.speak("Welcome to vismate!");
}

void VisMateClass::init_i2c(){
    Wire.begin(5, 6);
}

void VisMateClass::scan_i2c(){
    byte error, address;
    int nDevices = 0;

    debug(VIS_TAG, "Scanning for I2C devices ...");
    for(address = 0x01; address < 0x7f; address++){
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0){
        Serial.printf("I2C device found at address 0x%02X\n", address);
        nDevices++;
        } else if(error != 2){
        Serial.printf("Error %d at address 0x%02X\n", error, address);
        }
    }
    if (nDevices == 0){
        debug(VIS_TAG, "No I2C devices found");
    }
}
/*
void VisMateClass::screen(Menu_screen_t new_screen){
    _last_screen = _screen_now;
    _screen_now = new_screen;

    if(new_screen < 6 && new_screen > 0){
      _mode = new_screen;
      debugVal(VIS_TAG, "Mode : ", _mode);
    }

    // main menu
    if(_last_screen == SETTING && _screen_now == HOME_SCREEN){
        uint16_t angle = lcd.get_angle() - 20;
        for(int x = 240; x >= 0; x-=40){
            lcd.swipe(_last_screen, x-240, angle);
            lcd.swipe(_screen_now, x, angle);
        }    
        lcd.update_time(ntp.get_time(), ntp.get_date());
        debugVal(VIS_TAG, "1 Swipe to new screen : ", _screen_now);
        debugVal(VIS_TAG, "1 From last screen : ", _last_screen);
    
    }   else if(_last_screen == HOME_SCREEN && _screen_now == SETTING){
        uint16_t angle = lcd.get_angle() + 20;
        for(int x = 0; x <= 240; x+=40){
          lcd.swipe(_last_screen, x, angle);
          lcd.swipe(_screen_now, x-240, angle);
        }
        debugVal(VIS_TAG, "2 Swipe to new screen : ", _screen_now);
        debugVal(VIS_TAG, "2 From last screen : ", _last_screen);
    
    }   else if(_last_screen < _screen_now && _screen_now <= 5){
        uint16_t angle = lcd.get_angle() - 20;
        for(int x = 240; x >= 0; x-=40){
            lcd.swipe(_last_screen, x-240, angle);
            lcd.swipe(_screen_now, x, angle);
        }
        debugVal(VIS_TAG, "3 Swipe to new screen : ", _screen_now);
        debugVal(VIS_TAG, "3 From last screen : ", _last_screen);
    
    }   else if(_last_screen > _screen_now && _screen_now <= 5 && _last_screen <=5){        
        uint16_t angle = lcd.get_angle() + 20;
        for(int x = 0; x <= 240; x+=40){
            lcd.swipe(_last_screen, x, angle);
            lcd.swipe(_screen_now, x-240, angle);
        }
        if(_screen_now == HOME_SCREEN) lcd.update_time(ntp.get_time(), ntp.get_date());
        debugVal(VIS_TAG, "4 Swipe to new screen : ", _screen_now);
        debugVal(VIS_TAG, "4 From last screen : ", _last_screen);
    
    // app
    }   else if(_screen_now > 5 && _last_screen < 5){
        uint16_t angle = lcd.get_angle() - 20;
        for(int x = 240; x >= 0; x-=40){
            lcd.slide(_mode, x-240, angle);
            lcd.slide(_screen_now, x, angle);
        }
        debugVal(VIS_TAG, "5 Slide to new screen : ", _screen_now);
        debugVal(VIS_TAG, "5 From last screen : ", _last_screen);
        debugVal(VIS_TAG, "5 Mode : ", _mode);

    }   else if(_screen_now > 5 && _last_screen > 5){
        if(_last_screen < _screen_now){
            uint16_t angle = lcd.get_angle() - 20;
            for(int x = 240; x >= 0; x-=40){
                lcd.slide(_last_screen, x-240, angle);
                lcd.slide(_screen_now, x, angle);
            }
            debugVal(VIS_TAG, "6 Slide to new screen : ", _screen_now);
            debugVal(VIS_TAG, "6 From last screen : ", _last_screen);
            debugVal(VIS_TAG, "8 Mode : ", _mode);

        }   else if(_last_screen > _screen_now){  
            uint16_t angle = lcd.get_angle() + 20;      
            for(int x = 0; x <= 240; x+=40){
                lcd.slide(_last_screen, x, angle);
                lcd.slide(_screen_now, x-240, angle);
            }
            debugVal(VIS_TAG, "7 Slide to new screen : ", _screen_now);
            debugVal(VIS_TAG, "7 From last screen : ", _last_screen);
            debugVal(VIS_TAG, "7 Mode : ", _mode);
        }
    }   else if(_screen_now < 6 && _last_screen > 5){
        uint16_t angle = lcd.get_angle() + 20;
        for(int x = 0; x <= 240; x+=40){
            lcd.slide(_last_screen, x, angle);
            lcd.slide(_screen_now, x-240, angle);
        }
        _screen_now = _mode;
        debugVal(VIS_TAG, "8 Slide to new screen : ", _screen_now);
        debugVal(VIS_TAG, "8 From last screen : ", _last_screen);
        debugVal(VIS_TAG, "8 Mode : ", _mode);
        
    // error
    }   else{
        lcd.swipe(_screen_now, 0, lcd.get_angle());
        debugVal(VIS_TAG, "9 Error : ", _screen_now);
    }

    if(_volume > 0){
        vismate_instances->talk(_screen_now);
    }
}
 */
void VisMateClass::talk(Menu_screen_t screen_name){
    switch (screen_name) {
        case HOME_SCREEN:
            voice.speak("Home screen");
            break;
        case NOTES:
            voice.speak("Voice Notes");
            break;
        case SPEAK:
            voice.speak("Text to Speech");
            break;
        case NAVIGATION:
            voice.speak("Navigation");
            break;
        case MAPS:
            voice.speak("Maps");
            break;
        case SETTING:
            voice.speak("Setting");
            break;
        case HOME_MAPS:
            voice.speak("Location brawijaya");
            break;
        case SHOW_MAPS:
            voice.speak("Here is maps to Brawijaya University Malang");
            break;
        case LISTENING:
            voice.speak("Listening started");
            break;
        case LOADING:
            voice.speak("Processing data");
            break;
        default:
            voice.speak("Default");
            break;
    }
}

void VisMateClass::set_rotation(uint8_t rotation){
    _rotation = rotation;
    lcd.set_rotation(rotation);
}

uint8_t VisMateClass::get_rotation(){
    return lcd.get_rotation();
}

bool VisMateClass::get_network_status(){
    _network_status = net.get_status();
    return _network_status;
}

void VisMateClass::set_volume(uint8_t volume){
    _volume = volume;
    voice.change_volume(_volume);
}

uint8_t VisMateClass::get_volume(){
    return _volume;
}

Menu_screen_t VisMateClass::get_screen(){
    return _screen_now;
}

Menu_screen_t VisMateClass::get_last_screen(){
    return _last_screen;
}

void VisMateClass::setScreen(Menu_screen_t screen_name){
    _screen_now = screen_name;
}

VisMateClass vismate;
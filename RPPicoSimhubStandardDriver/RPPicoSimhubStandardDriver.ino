#include "enums.h"
#include "externaldefines.h"

//-------------------------
// ------- General sketch informations
//-------------------------
// This sketch is delivered as a simple SimHub compatible Raspberry Pi Pico/Pico2 device driver.

// Default settings (keep externaldefines.h empty to use them !!)
#ifndef EXTERNAL_DEFINES

//-------------------------
// ------- Upload protection settings
//-------------------------
// Set to 1 to enable upload protection, upload from Arduino IDE will be disabled after the specified delay (UPLOAD_AVAILABLE_DELAY),
// This can be unlocked using one of the following ways :
// - by unplugging/plugging back the arduino, upload will be enabled for the defined time.
// - by sending the magic string on the serial port : (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)unloc
#define ENABLE_UPLOAD_PROTECTION 0
// Delay (in ms) after the arduino startup (plug/unplug/reset) where the upload will be available, after this delay upload will be locked.
#define UPLOAD_AVAILABLE_DELAY 15000

//-------------------------
// ------- Device description
//-------------------------
// Allow automatic detection
// 0 = off, 1 = on
#define DEVICE_AUTODETECT_ALLOWED 1

// The following options are only used when DEVICE_AUTODETECT_ALLOWED is set to 1 (DEVICE_TYPE,DEVICE_NAME, DEVICE_NAME, DEVICE_BRAND, DEVICE_PICTURE_URL)

// Your device type, when DEVICE_AUTODETECT_ALLOWED is set to 1
// DEVICETYPE_UNSPECIFIED = No automatic detection possible
// DEVICETYPE_LEDS_PLUS_VOCORE = Will be detected as a led device + VOCORE
// DEVICETYPE_LEDS_PLUS_USBD480 = Will be detected as a led device + USBD480
// DEVICETYPE_LEDS_PLUS_MONITOR = Will be detected as a led device + a windows monitor (HDMI etc ...)
// DEVICETYPE_MATRIX = Will be detected as a single matrix device
// DEVICETYPE_MATRIX_PLUS_LEDS = Will be detected as a single matrix device associated with a led strip
// DEVICETYPE_FANS = Will be detected as a fan device
#define DEVICE_TYPE DEVICETYPE_UNSPECIFIED

// Your device name
#define DEVICE_NAME "My device"

// Your device brand name
#define DEVICE_BRAND "My brand"

// Your device VID
#define DEVICE_VID 0x2e8a

// Your device PID
#define DEVICE_PID 0xffff

// Your device picture (512 px width or 512 px height minimum), with transparent background and properly cropped.
// Please use a  reliable and fast hosting : ONCE FLASHED THE URL WILL BE PERMANENT and must be alive at least for the expected life of the device.
// A public GitHub repo can be a good long term and reliable solution to store this picture.
#define DEVICE_PICTURE_URL "https://simhubdash.com/devices/nopicture.png"

//-------------------------
// ------- LED STRIP #1 Settings
//-------------------------
// How many leds on this strip? Set to 0 to disable.
#define STRIP1_RGBLEDCOUNT 8
// Data pin
#define STRIP1_DATAPIN 2
// 0 left to right, 1 right to left
#define STRIP1_RIGHTTOLEFT 0
// Strip max brightness (0-255), use it to maximum allowed power consumption for the strip
#define STRIP1_MAX_BRIGHTNESS 255

//-------------------------
// ------- STRIP #2 Settings
//-------------------------
// How many leds on this strip? Set to 0 to disable.
#define STRIP2_RGBLEDCOUNT 0
// Data pin
#define STRIP2_DATAPIN 7
// 0 left to right, 1 right to left
#define STRIP2_RIGHTTOLEFT 0
// Strip max brightness (0-255), use it to maximum allowed power consumption for the strip
#define STRIP2_MAX_BRIGHTNESS 255

//-------------------------
// ------- STRIP #3 Settings
//-------------------------
// How many leds on this strip? Set to 0 to disable.
#define STRIP3_RGBLEDCOUNT 0
// Data pin
#define STRIP3_DATAPIN 8
// 0 left to right, 1 right to left
#define STRIP3_RIGHTTOLEFT 0
// Strip max brightness (0-255), use it to maximum allowed power consumption for the strip
#define STRIP3_MAX_BRIGHTNESS 255

//-------------------------
// ------- STRIP #4 Settings
//-------------------------
// How many leds on this strip? Set to 0 to disable.
#define STRIP4_RGBLEDCOUNT 0
// Data pin
#define STRIP4_DATAPIN 9
// 0 left to right, 1 right to left
#define STRIP4_RIGHTTOLEFT 0
// Strip max brightness (0-255), use it to maximum allowed power consumption for the strip
#define STRIP4_MAX_BRIGHTNESS 255

//-------------------------
// ------- LEDs usage description
//-------------------------
// Describe in order the usage for each leds, it be either a telemetry led or button

// LX : Led #X in SimHub, numbers are "0" based (first led is L0 in SimHub)
// BX : Button #X in SimHub, numbers are "0" based (first led is L0 in SimHub)

// Example "L0,L1,L2,B0,B0,B1,B1,B2,B2,B2"
// A led or a button can be used multiple times if needed (IE if the 4 first LEDs are tied to the first button : B0,B0,B0,B0 ...
// If nothing is specified all leds will be used as a telemetry leds.
#define LEDS_LAYOUT ""

// Default buttons colors at connection
// Example "#FFFFFF,#FFFFFF"
#define DEFAULT_BUTTONS_COLORS ""

//-------------------------
// ------- 8x8 WS2812B RGB Matrix Settings
//-------------------------
// Enable matrix support ? Set to 0 to disable.
#define MATRIX_ENABLED 1
// Data pin
#define MATRIX_DATAPIN 6
// Matrix max brightness (0-255), use it to maximum allowed power consumption for the matrix
#define MATRIX_MAX_BRIGHTNESS 128
// Matrix led layout
// MATRIX_LEFTTORIGHT : left ro right for each row ,
// MATRIX_SERPENTINE : left to right, then right to left etc ..
// MATRIX_REVERSESERPENTINE :right to left, then left to right etc ..
#define MATRIX_LAYOUT MATRIX_LEFTTORIGHT

// Default hardware matrix rotation, 0,90 ,180, 270 
#define MATRIX_ROTATION 0

//-------------------------
// ------- Fan controller settings
//-------------------------
// FANS_NOFAN = Disabled
// FANS_25KHZPWM = 25KHZ PWM fans with optional relay
// FANS_CUSTOM = Custom fans (see fanscustom.h to implement)
#define FANS_CONTROLLER FANS_NOFAN

//-------------------------
// ------- PWM FANS SETTING (FANS_CONTROLLER == 1) 
//-------------------------
// How many PWM fans are enabled (only enabled fans will get initialized)
#define PWMFANS_COUNT 1

// PWMFANS_PIN_XX : Fan pin (CAN BE ONLY 9 10 or 11 on an ATMEGA32U4)
// PWMFANS_MIN_OUTPUT_XX : 0 to 1023, minimum PWM value, otherwise the output is set to 0
// PWMFANS_MAX_OUTPUT_XX 0 to 1023 : 0 to 1023, maximum PWM value,the input is scaled based on it.
// PWMFANS_RELAY_PIN_XX : relay pin (set to -1 to disable)
// PWMFANS_RELAY_DELAY_XX : after how much time the fan is set set to 0 the relay will get disabled
// PWMFANS_RELAY_REVERSELOGIC_XX : Relay logic ( ON = HIGH or ON = LOW)

// First Fan
#define PWMFANS_PIN_O1 9
#define PWMFANS_MIN_OUTPUT_O1 0
#define PWMFANS_MAX_OUTPUT_O1 1023
#define PWMFANS_RELAY_PIN_01 -1
#define PWMFANS_RELAY_DELAY_01 2000
#define PWMFANS_RELAY_REVERSELOGIC_01 1

// Second Fan
#define PWMFANS_PIN_O2 10
#define PWMFANS_MIN_OUTPUT_O2 0
#define PWMFANS_MAX_OUTPUT_O2 1023
#define PWMFANS_RELAY_PIN_02 -1
#define PWMFANS_RELAY_DELAY_02 2000
#define PWMFANS_RELAY_REVERSELOGIC_02 0

// Third Fan
#define PWMFANS_PIN_O3 11
#define PWMFANS_MIN_OUTPUT_O3 0
#define PWMFANS_MAX_OUTPUT_O3 1023
#define PWMFANS_RELAY_PIN_03 -1
#define PWMFANS_RELAY_DELAY_03 2000
#define PWMFANS_RELAY_REVERSELOGIC_03 0

//-------------------------
// ------- CUSTOM FANS SETTING (FANS_CONTROLLER == 99) 
//-------------------------

// See fanscustom.h to implement

#endif

// To enable custom device names, VID and PID for RP Pico/Pico2
#include <Adafruit_TinyUSB.h>

// Main simhub command processing
#include "protocol.h"

/// <summary>
/// Initialize the arduino.
/// </summary>
void setup() {

	Serial.begin(115200);

	// Assign custom data callback
	customSerialDataCallback = &onCustomSerialData;

	setupLeds();
	setupMatrix();
	setupFans();
}

/// <summary>
/// Put your setup code to run on core 2 here.
/// </summary>
void setup1(){
  TinyUSBDevice.setManufacturerDescriptor(DEVICE_BRAND);
  TinyUSBDevice.setProductDescriptor(DEVICE_NAME);
  TinyUSBDevice.setID(DEVICE_VID, DEVICE_PID);

  if (!TinyUSBDevice.isInitialized()){
    TinyUSBDevice.begin(0);
  }
  if (TinyUSBDevice.mounted()){
    TinyUSBDevice.detach();
    delay(50);
    TinyUSBDevice.attach();
  }
}

/// <summary>
/// Callback when custom serial data is incoming
/// </summary>
/// <param name="messageLength">The length of the incoming message</param>
/// read it using usual Serial.read() etc,
/// make sure to read exactly and completely your whole message
/// (messageLength is provided so you know exactly how much bytes must be read.)
void onCustomSerialData(int messageLength) {
	// Simple echo example
	Serial.println("Custom command received");
	for (int i = 0; i < messageLength; i++) {
		// Wait for the byte
		while (!Serial.available()) {
		}
		Serial.write((char)Serial.read());
	}
	Serial.println();
}

/// <summary>
/// Main loop.
/// </summary>
void loop() {
	processCommands();
}

/// <summary>
/// Main loop for core 2.
/// </summary>
void loop1() {

}



#ifndef SUPREMA_H
#define SUPREMA_H

#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <asm-generic/ioctl.h>
//#include <asm-generic/types.h>

// Device Name

#define DEVICE "/dev/ttyUSB0";
#define TRUE 1
#define FALSE 0

// Headers

#define START 0x40
#define END 0x0A

// Commands *** System Configuration

//#define SW 0x01; // Write system parameter
//#define SF 0x02; // Save system parameter
#define SR 0x03; // Read system parameter
//#define CS 0x1A; // Calibrate sensor
//#define SS 0x04; // Check system status
//#define CA 0x60; // Cancel
//#define ID 0x85; // Get the module ID
//#define UG 0x62; // Upgrade firmware
//#define RS 0xD0; // Reset the module
//#define LM 0xB1; // Lock the module
//#define UM 0xB0; // Unlock the module
//#define MP 0xB2; // Change the master password
//#define OFF 0xD2; // Turn off the module

//// Commands *** Enroll

#define ES 0x05 // Enroll by scan
//#define ESA 0x70; // ES with administrator’s verification
#define EI 0x06 // Enroll by image
//#define EIX 0x80; // EI with extended data transfer protocol
#define ET 0x07; // Enroll by template
//#define ETX 0x87; // ET with extended data transfer protocol
//#define EW 0x1C; // Enroll by Wiegand ID
//#define EWA 0x71; // EW with administrator’s verification

// Commands *** Verify

#define VS 0x08 // Verify by scan
#define VI 0x09 // Verify by image
//#define VIX 0x82; // VI with extended data transfer protocol
//#define VT 0x10; // Verify by template
//#define VW 0x1D; // Verify by Wiegand ID
//#define VH 0x22; // Verify host template by scan
//#define WSL 0x6B; // Write security level of a user
//#define RSL 0x6C; // Read security level of a user

// Commands *** Identify
#define IS 0x11 // Identify by scan
#define II 0x12 // Identify by image
//#define IIX 0x81; // II with extended data transfer protocol
//#define IT 0x13; // Identify by template

// Commands *** Delete

#define DA 0x17 // Delete all templates
#define DAA 0x74 // DA with administrator’s verification
#define DT 0x16 // Delete template
#define DS 0x1E // Delete by scan
#define DSA 0x72 // DS with administrator’s verification
//#define DW 0x1F; // Delete by Wiegand ID
//#define DWA 0x73; // DW with administrator’s verification

// Commands *** Template management

#define LT 0x18 // List user ID
//#define LTX 0x86; // List user ID with extended data transfer protocol
#define CT 0x19 // Check user ID
//#define FP 0x23; // Fix all provisional templates
//#define DP 0x24; // Delete all provisional templates

// Commands Get image and template

#define RI 0x20 // Read image
//#define RIX 0x84; // RI with extended data transfer protocol
#define SI 0x15 // Scan image
//#define SIX 0x83; // SI with extended data transfer protocol
#define RT 0x14 // Read template
//#define RTX 0x89; // RT with extended data transfer protocol
#define ST 0x21 // Scan template
//#define KS 0x35; // Scan template with challenge data
//#define KW 0x34; // Write encryption key
#define NumberEnrolledFinger 0x73
#define NumberAvailableEnrolledFinger 0x74

// ************************************************************************* //

// FLAGs

#define CHECK_ID 0x70 // Check if the requested user ID exists
#define ADD_NEW 0x71 // Adding more fingerprints to a current existing user ID.
#define CONTINUE 0x74 // There is more data to be sent.
#define AUTO_ID 0x79 // Automatically assign user ID in enrollment.
#define CHECK_FINGER 0x84 // Check if the finger is already enrolled.
#define CHECK_FINGER_AUTO_ID 0x85 // Check if the finger is already enrolled. If not, assign user ID automatically.
#define ADD_DURESS 0x92 // Add duress fingerprints to an existing user ID.

// ERROR Codes

#define SUCCESS 0x61
#define SCAN_SUCCESS 0x62
#define SCAN_FAIL 0x63
#define NOT_FOUND 0x69
#define NOT_MATCH 0x6A
#define TRY_AGAIN 0x6B
#define TIME_OUT 0x6C
#define MEM_FULL 0x6D
#define EXIST_ID 0x6E
#define FINGER_LIMIT 0x72
#define UNSUPPORTED 0x75
#define INVALID_ID 0x76
#define TIMEOUT_MATCH 0x7A
#define BUSY 0x80
#define CANCELED 0x81
#define DATA_ERROR 0x82
#define DATA_OK 0x83
#define EXIST_FINGER 0x86
#define DURESS_FINGER 0x91
#define LOCKED 0xA1
#define REJECTED_ID 0x90
#define ENTRANCE_LIMIT 0x94
#define FAKE_DETECTED 0xB0

//

//Response Code

#define RECV_CORRECT 0x01
#define RECV_ERROR 0x02
#define OP_SUCCESS 0x31
#define FINGER_DETECT 0x32
//#define TIME_OUT 0x33
#define FINGER_FALIURE 0x34
#define PARAM_ERROR 0x35
#define FINGER_MATCH_ID 0x37
#define NO_FINGER_MATCH_ID 0x38
#define FINGER_FOUND 0x39
#define FINGER_NOT_FOUND 0x3A

#define ISstring "11"
#define RTstring "14"
#define ETstring "07"
#define ESstring "05"
#define DAstring "17"
#define DTstring "16"
#define CTstring "19"
#define SUCCESSstring "61"
#define SCAN_SUCCESSstring "62"
#define NOT_FOUNDstring "69"
#define CONTINUEstring "74"
#define EXIST_IDstring "6e"
#define TIME_OUTstring "6c"

#define MEM_FULLstring "6D"
#define FINGER_LIMITstring "72"
#define EXIST_FINGERstring "86"
#define NOT_MATCHstring "6A"
#define NumberAvailableEnrolledFingerstring "74"
#define NumberEnrolledFingerstring "73"
#define SRstring "03"
#endif // SUPREMA_H

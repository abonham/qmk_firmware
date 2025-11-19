// 1000hz Polling Rate
#define USB_POLLING_INTERVAL_MS 4
#define QMK_KEYS_PER_SCAN 12
// #define MASTER_RIGHT 1
// #define OS_DETECTION_KEYBOARD_RESET //change this next if no luck
#define OS_DETECTION_SINGLE_REPORT
#ifdef DEVICE_VER
#undef DEVICE_VER
#endif
#define DEVICE_VER 0x0010
#ifdef MANUFACTURER
#undef MANUFACTURER
#endif
#define MANUFACTURER "Flower"
#define SPLIT_HAND_PIN D1

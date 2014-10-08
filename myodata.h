#pragma once

#include <stdint.h>

#ifdef _MSC_VER
# pragma pack(push, 1)
# define PACKED
#else
# define PACKED __attribute__ ((__packed__))
#endif // _MSC_VER

typedef enum {
    myodata_event_pose        = 1,
    myodata_event_orientation = 2,
} myodata_event_t;

typedef struct PACKED {
    uint8_t event_type;
    uint8_t myo_id;
    uint16_t pose;
} myodata_event_pose_t;

static const int16_t RPY_SCALE = 10000;

typedef struct PACKED {
    uint8_t event_type;
    uint8_t myo_id;
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
} myodata_event_orientation_t;

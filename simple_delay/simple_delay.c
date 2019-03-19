//
// Created by vinzenz on 3/19/19.
//

#include <math.h>
#include <stdlib.h>

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#define SIMPLE_DELAY_URI "https://github.com/expertanalytics/lv2-plugins/tree/master/simple_delay"


typedef enum {
    AMP_INPUT  = 0,
    AMP_OUTPUT = 1
} PortIndex;


typedef struct {
    // Port buffers
    const float* input;
    float*       output;
    float*       delay_line1;
} SimpleDelay;


static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{
    SimpleDelay* simple_delay = (SimpleDelay*)calloc(1, sizeof(SimpleDelay));

    return (LV2_Handle)simple_delay;
}


static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
    SimpleDelay* delay = (SimpleDelay*)instance;

    switch ((PortIndex)port) {
        case AMP_INPUT:
            delay->input = (const float*)data;
            break;
        case AMP_OUTPUT:
            delay->output = (float*)data;
            break;
    }

}

static void
activate(LV2_Handle instance)
{
}

static void
run(LV2_Handle instance, uint32_t n_samples)
{
    SimpleDelay* delay = (SimpleDelay*)instance;

    const float* const input  = delay->input;
    float* const       delay_line1 = delay->delay_line1;
    float* const       output = delay->output;

    for (uint32_t pos = 0; pos < n_samples; pos++) {
        output[pos] = input[pos]+delay_line1[pos];
        delay_line1[pos] = input[pos];
    }

}

static void
deactivate(LV2_Handle instance)
{
}

static void
cleanup(LV2_Handle instance)
{
    free(instance);
}

static const void*
extension_data(const char* uri)
{
    return NULL;
}


static const LV2_Descriptor descriptor = {
        SIMPLE_DELAY_URI,
        instantiate,
        connect_port,
        activate,
        run,
        deactivate,
        cleanup,
        extension_data
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
switch (index) {
case 0:  return &descriptor;
default: return NULL;
}
}
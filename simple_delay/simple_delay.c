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
    long         buffer_size;
    int          input_pos;
} SimpleDelay;


static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{
    SimpleDelay* simple_delay = (SimpleDelay*)calloc(1, sizeof(SimpleDelay));
    simple_delay->buffer_size = 26500;
    simple_delay->delay_line1 = malloc(26500*sizeof(float));
    simple_delay->input_pos = 0;

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
    int                input_pos = delay->input_pos;
    long const         buffer_size = delay->buffer_size;

    int delay_pos;

    for (uint32_t pos = 0; pos < n_samples; pos++) {
        delay_pos = (pos+input_pos)%buffer_size;
        output[pos] = input[pos]+delay_line1[delay_pos];
        delay_line1[delay_pos] = input[pos];
    }
    input_pos += n_samples;
    input_pos %= buffer_size;

}

static void
deactivate(LV2_Handle instance)
{
}

static void
cleanup(LV2_Handle instance)
{
    SimpleDelay* delay = (SimpleDelay*)instance;
    free(delay->delay_line1);
    free(delay);
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
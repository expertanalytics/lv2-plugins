//
// Created by vinzenz on 3/19/19.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#define LOWPASS_URI "https://github.com/expertanalytics/lv2-plugins/tree/master/lowpass"

typedef enum {
    INPUT_PORT  = 0,
    OUTPUT_PORT = 1,
    CUTOFF_PORT = 2,
} PortIndex;


typedef struct {
    // Port buffers
    const float* input;
    float*       output;
    float        transition_y;
    const float* cutoff;
    double       rate;
} Lowpass;


/*
 * Instantiates a plugin.
 */
static LV2_Handle
instantiate(
    const LV2_Descriptor* descriptor,
    double                rate,
    const char*           bundle_path,
    const LV2_Feature* const* features
) {
    Lowpass* lowpass = (Lowpass*)calloc(1,sizeof(Lowpass));
    lowpass->transition_y = 0.0;
    lowpass->rate = rate;
    return (LV2_Handle)lowpass;
}

/*
 * connect_port is called by the host to connect a port to a buffer.
 */
static void
connect_port(
    LV2_Handle instance,
    uint32_t   port,
    void*      data
) {
    Lowpass* lowpass = (Lowpass*)instance;
    switch ((PortIndex)port) {
        case INPUT_PORT:
            lowpass->input = (const float*)data;
            break;
        case OUTPUT_PORT:
            lowpass->output = (float*)data;
            break;
        case CUTOFF_PORT:
            lowpass->cutoff = (const float*)data;
            break;
    }
}

/*
 * Activates a plugin instance. Is called before run().
 */
static void
activate(LV2_Handle instance) {
    Lowpass* lowpass = (Lowpass*)instance;
    lowpass->transition_y = 0;
}

/*
 * Run a plugin instance for a block
 */
static void
run(LV2_Handle instance, uint32_t n_samples) {
    Lowpass* lowpass = (Lowpass*)instance;

    double alpha = *lowpass->cutoff / lowpass->rate;
    float y0 = lowpass->transition_y;
    const float* const x = lowpass->input;
    float* const       y = lowpass->output;

    // y[i] := α * x[i] + (1-α) * y[i-1]

    y[0] = y0 + alpha * (x[0] - y0);

    for (uint32_t pos = 0; pos < n_samples-1; pos++) {
        y[pos+1] = y[pos] + alpha * (x[pos+1] - y[pos]);
    }

    lowpass->transition_y = y[n_samples-1];
}

/*
 * Deactivates a plugin instance. Is called after run().
 */
static void
deactivate(LV2_Handle instance) {
}

/*
 * Cleanes up a plugin instance. Is the counterpart to instantiate.
 */
static void
cleanup(LV2_Handle instance){
    Lowpass* lowpass = (Lowpass*)instance;
    free(lowpass);
}

/*
 * Returns additional plugin data. Typically used to return a struct with functions pointers
 * to extend the LV2_Descriptor API.
 */
static const void*
extension_data(const char* uri)
{
    return NULL;
}


static const LV2_Descriptor descriptor = {
        LOWPASS_URI,
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
/*
 * A plugin accessor. Plugings are accessed by index using values from 0 and up.
 * Out of range indices must return NULL.
 */
lv2_descriptor(uint32_t index){
    switch (index) {
        case 0:  return &descriptor;
        default: return NULL;
    }
}

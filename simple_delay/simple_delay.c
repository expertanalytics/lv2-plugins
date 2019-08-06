//
// Created by vinzenz on 3/19/19.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#define SIMPLE_DELAY_URI "https://github.com/expertanalytics/lv2-plugins/tree/master/simple_delay"


typedef enum {
    INPUT_PORT  = 0,
    OUTPUT_PORT = 1,
    DELAY_TIME_PORT = 2,
    FEEDBACK_PORT = 3,
    DRY_WET_PORT = 4,
    OUTPUT_GAIN = 5,
} PortIndex;


typedef struct {
    // Port buffers
    const float* input;
    float*       output;
    float*       delay_line1;
    long         buffer_size;
    int          input_pos;
    const float* delay_time;
    const float* feedback;
    const float* dry_wet_amount;
    const float* output_gain;
} SimpleDelay;


static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{
    printf("instantiate\n");
    SimpleDelay* simple_delay = (SimpleDelay*)calloc(1, sizeof(SimpleDelay));
    simple_delay->buffer_size = 22050*2;
    simple_delay->delay_line1 = malloc(((int)simple_delay->buffer_size)*sizeof(float));
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
        case INPUT_PORT:
            delay->input = (const float*)data;
            break;
        case OUTPUT_PORT:
            delay->output = (float*)data;
            break;
        case DELAY_TIME_PORT:
            printf("Connect ports: index %u \n", port);
            delay->delay_time = (const float*)data;
        case FEEDBACK_PORT:
            printf("Connect ports: index %u \n", port);
            delay->feedback = (const float*)data;
        case DRY_WET_PORT:
            printf("Connect ports: index %u \n", port);
            delay->dry_wet_amount = (const float*)data;
        case OUTPUT_GAIN:
            printf("Connect ports: index %u \n", port);
            delay->output_gain = (const float*)data;
    }

}

static void
activate(LV2_Handle instance)
{
    SimpleDelay* delay = (SimpleDelay*)instance;
    long const         buffer_size = delay->buffer_size;
    float* const       delay_line1 = delay->delay_line1;
    for(uint32_t i = 0; i < buffer_size; i++){
        delay_line1[i] = 0;
    }
 //   printf("activating\n");
}


#define DB_CO(g) ((g) > -90.0f ? powf(10.0f, (g) * 0.05f) : 0.0f)

static void
run(LV2_Handle instance, uint32_t n_samples)
{
    SimpleDelay* delay = (SimpleDelay*)instance;

    const float* const input  = delay->input;
    float* const       delay_line1 = delay->delay_line1;
    float* const       output = delay->output;
    int                input_pos = delay->input_pos;
    long const         buffer_size = delay->buffer_size;
    const float        delay_time = fabs(*(delay->delay_time))/1000.f; // ms

    const float        dry_wet_amount = fabs(*(delay->dry_wet_amount)/100.);
    const float        feedback = fabs(*(delay->feedback)/100.);

    const float        output_gain = DB_CO(*(delay->output_gain));

    int delay_pos_input;
    float delay_signal;
    float y1;
    float y2;
    int sample_rate = 44100; // Hz

    float delayed_pos = (input_pos-(delay_time*sample_rate));
    if (delayed_pos < 0) {
        delayed_pos += buffer_size;
    }
    int x1 = (int)delayed_pos;
    int x2 = (x1+1)%buffer_size;
    float lam = x2-delayed_pos;


    for (uint32_t pos = 0; pos < n_samples; pos++) {
        delay_pos_input = (pos + input_pos) % buffer_size;

        y1 = delay_line1[(x1+pos)%buffer_size];
        y2 = delay_line1[(x2+pos)%buffer_size];
        delay_signal = y2 + lam*(y1-y2);
        //delay_signal = y1;
        output[pos] = output_gain * (input[pos] * (1.-dry_wet_amount) + dry_wet_amount * delay_signal);
        // output_gain
        delay_line1[delay_pos_input] = input[pos] + feedback * output[pos];
    }
    input_pos += n_samples;
    input_pos %= buffer_size;
    delay->input_pos = input_pos;

}

static void
deactivate(LV2_Handle instance)
{
   // printf("deactivate\n");
}

static void
cleanup(LV2_Handle instance)
{
    //printf("cleaning up\n");
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

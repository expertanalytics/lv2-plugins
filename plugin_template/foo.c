//
// Created by vinzenz on 3/19/19.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#define q "https://github.com/expertanalytics/lv2-plugins/tree/master/foo"


typedef enum {
    INPUT_PORT  = 0,
    OUTPUT_PORT = 1,
} PortIndex;


typedef struct {
    // Port buffers
    const float* input;
    float*       output;
} Foo;


static LV2_Handle
instantiate(
    const LV2_Descriptor* descriptor,
    double                rate,
    const char*           bundle_path,
    const LV2_Feature*
    const* features,
)
{
    Foo* foo = (Foo*)malloc(sizeof(foo));

    return (LV2_Handle)foo;
}


static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
    Foo* foo = (Foo*)instance;

    switch ((PortIndex)port) {
        case INPUT_PORT:
            foo->input = (const float*)data;
            break;
        case OUTPUT_PORT:
            foo->output = (float*)data;
            break;
    }
}

static void
activate(LV2_Handle instance) {}

static void
run(LV2_Handle instance, uint32_t n_samples) {}

static void
deactivate(LV2_Handle instance) {}

static void
cleanup(LV2_Handle instance){
    free(instance);
}

static const void*
extension_data(const char* uri)
{
    return NULL;
}


static const LV2_Descriptor descriptor = {
        FOO_URI,
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

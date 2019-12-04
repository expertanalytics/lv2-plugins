//
// Created by vinzenz on 3/19/19.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#define PLUGIN_NAME_PLACEHOLDER_URI "https://github.com/expertanalytics/lv2-plugins/tree/master/plugin_name_placeholder"


typedef enum {
    INPUT_PORT  = 0,
    OUTPUT_PORT = 1,
} PortIndex;


typedef struct {
    // Port buffers
    const float* input;
    float*       output;
} TypeNamePlaceholder;


/*
 * Instanciates a plugin.
 */
static LV2_Handle
instantiate(
    const LV2_Descriptor* descriptor,
    double                rate,
    const char*           bundle_path,
    const LV2_Feature* const* features)
{
    TypeNamePlaceholder* plugin_name_placeholder = (TypeNamePlaceholder*)malloc(sizeof(plugin_name_placeholder));

    return (LV2_Handle)plugin_name_placeholder;
}

/*
 * connect_port is called by the host to connect a port to a buffer.
 */
static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
    TypeNamePlaceholder* plugin_name_placeholder = (TypeNamePlaceholder*)instance;

    switch ((PortIndex)port) {
        case INPUT_PORT:
            plugin_name_placeholder->input = (const float*)data;
            break;
        case OUTPUT_PORT:
            plugin_name_placeholder->output = (float*)data;
            break;
    }
}

/*
 * Activates a plugin instance. Is called before run().
 */
static void
activate(LV2_Handle instance) {}

/*
 * Run a plugin instance for a block
 */
static void
run(LV2_Handle instance, uint32_t n_samples) {}

/*
 * Deactivates a plugin instance. Is called after run().
 */
static void
deactivate(LV2_Handle instance) {}

/*
 * Cleanes up a plugin instance. Is the counterpart to instanciate.
 */
static void
cleanup(LV2_Handle instance){
    free(instance);
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
        PLUGIN_NAME_PLACEHOLDER_URI,
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
lv2_descriptor(uint32_t index)
{
switch (index) {
case 0:  return &descriptor;
default: return NULL;
}
}

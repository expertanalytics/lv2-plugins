//
// Created by vinzenz on 3/19/19.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fftw3.h>

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#define SIMPLE_LOWPASS_FFT_URI "https://github.com/expertanalytics/lv2-plugins/tree/master/simple_lowpass_fft"


typedef enum {
    INPUT_PORT  = 0,
    OUTPUT_PORT = 1,
} PortIndex;


typedef struct {
    // Port buffers
    const float*  input;
    float*        output;
} SimpleLowpassFft;


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
    SimpleLowpassFft* simple_lowpass_fft = (SimpleLowpassFft*)malloc(sizeof(SimpleLowpassFft));
    return (LV2_Handle)simple_lowpass_fft;
}

/*
 * connect_port is called by the host to connect a port to a buffer.
 */
static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
    SimpleLowpassFft* simple_lowpass_fft = (SimpleLowpassFft*)instance;

    switch ((PortIndex)port) {
        case INPUT_PORT:
            simple_lowpass_fft->input = (const float*)data;
            break;
        case OUTPUT_PORT:
            simple_lowpass_fft->output = (float*)data;
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
run(LV2_Handle instance, uint32_t n_samples) {
    SimpleLowpassFft* simple_lowpass_fft = (SimpleLowpassFft*)instance;

    const float* const x = simple_lowpass_fft->input;
    float* const       y = simple_lowpass_fft->output;

    /*
     * Forward transformation to fourier room
     */
    double* input = (double*)malloc(sizeof(double)*n_samples);
    for (uint32_t pos = 0; pos < n_samples; pos++) {
        input[pos] = x[pos];
    }

    double* y_dash = (double*)malloc(sizeof(double)*n_samples);
    int n = (n_samples/2)+1;
    fftw_complex* X = (fftw_complex*)fftw_alloc_complex(sizeof(fftw_complex) * n);


    fftw_plan input_to_F_plan = fftw_plan_dft_r2c_1d(n_samples, input, X, FFTW_ESTIMATE);

    fftw_execute(input_to_F_plan);
    fftw_destroy_plan(input_to_F_plan);

    /*
     * Convolution with H == F(g)
     */
//    for (uint32_t pos = 0; pos < n; pos++) {
//        X[pos] = X[pos] * 1.0;
//    }

    /*
     * Backward transformationn
     */
    fftw_plan output_to_f_plan = fftw_plan_dft_c2r_1d(n_samples, X, y_dash, FFTW_ESTIMATE);

    fftw_execute(output_to_f_plan);
    fftw_destroy_plan(output_to_f_plan);

    for (uint32_t pos = 0; pos < n_samples; pos++) {
        /*
         * normalize output by number of samples to take account of 2 ffts
         */
        y[pos] = y_dash[pos]/n_samples;
    }
//    printf("%f \n",y[0]/input[0]);
    /*
     * Free memory
     */
    fftw_free(X);
    fftw_free(y_dash);
}

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
        SIMPLE_LOWPASS_FFT_URI,
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

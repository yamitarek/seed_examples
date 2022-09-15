#include "daisysp.h"
#include "daisy_seed.h"

using namespace daisysp;
using namespace daisy;

static DaisySeed  hw;
static Oscillator osc;
static Oscillator osc2;
static Oscillator osc3;
static Oscillator osc4;


static void AudioCallback(AudioHandle::InterleavingInputBuffer  in,
                      AudioHandle::InterleavingOutputBuffer out,
                          size_t                                size)
{
    float sig;
    float sig2;
    float sig3;
    float sig4;
    float freq;

    float amount_fm1;
    float amount_fm2;
    float amount_fm3;

    for(size_t i = 0; i < size; i += 2)
    {   



        freq = hw.adc.GetFloat(0)*900 + 100;
        amount_fm1 = hw.adc.GetFloat(1)*2;
        amount_fm2 = hw.adc.GetFloat(2)*2;
        amount_fm3 = hw.adc.GetFloat(3)*2;

        
        osc.SetFreq(freq);
        sig = osc.Process();

        osc2.SetFreq(freq + freq*sig*amount_fm1);
        sig2 = osc2.Process();

        osc3.SetFreq(freq + freq*sig2*amount_fm2);
        sig3 = osc3.Process();

        osc4.SetFreq(freq + freq*sig3*amount_fm3);
        sig4 = osc4.Process();

        // left out
        out[i] =  sig4;

        // right out
        out[i + 1] =  sig4;
    }
}

int main(void)
{
    // initialize seed hardware and oscillator daisysp module
    float sample_rate;
    hw.Configure();
    hw.Init();
    hw.SetAudioBlockSize(4);
    sample_rate = hw.AudioSampleRate();
    osc.Init(sample_rate);
    osc2.Init(sample_rate);
    osc3.Init(sample_rate);
    osc4.Init(sample_rate);

    //This is our ADC configuration
    const int num_adc_channels = 4;
    AdcChannelConfig adcConfig[num_adc_channels];
    //Configure pin 21 as an ADC input. This is where we'll read the knob.
    adcConfig[0].InitSingle(hw.GetPin(15));
    adcConfig[1].InitSingle(hw.GetPin(16));
    adcConfig[2].InitSingle(hw.GetPin(17));
    adcConfig[3].InitSingle(hw.GetPin(18));
    //Initialize the adc with the config we just made
    hw.adc.Init(adcConfig, num_adc_channels);
    //Start reading values
    hw.adc.Start();


    // Set parameters for oscillator
    osc.SetWaveform(osc.WAVE_SIN);
    osc2.SetWaveform(osc2.WAVE_SIN);
    osc3.SetWaveform(osc3.WAVE_SIN);
    osc4.SetWaveform(osc3.WAVE_SIN);

    osc.SetFreq(200);
    osc.SetAmp(1);
    osc2.SetFreq(400);
    osc2.SetAmp(1);
    osc3.SetFreq(0.2);
    osc3.SetAmp(1);
    osc4.SetFreq(200);
    osc4.SetAmp(1);


    // start callback
    hw.StartAudio(AudioCallback);


    while(1) {}
}

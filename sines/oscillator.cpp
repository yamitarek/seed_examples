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
    float freq2;
    float freq3;
    float freq4;
    
    for(size_t i = 0; i < size; i += 2)
    {
        freq = hw.adc.GetFloat(0)*900+100;
        freq2 = hw.adc.GetFloat(1)*900+100;
        freq3 = hw.adc.GetFloat(2)*900+100;
        freq4 = hw.adc.GetFloat(3)*900+100;
        
        
        osc.SetFreq(freq);
        osc2.SetFreq(freq2);
        osc3.SetFreq(freq3);
        osc4.SetFreq(freq4);
        
        
        sig = osc.Process();
        sig2 = osc2.Process();
        sig3 = osc3.Process();
        sig4 = osc4.Process();
        
        // left out
        out[i] = sig + sig2 + sig3+ sig4;

        // right out
        out[i + 1] = sig + sig2 + sig3+ sig4;
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
    osc2.SetWaveform(osc.WAVE_SIN);
    osc3.SetWaveform(osc.WAVE_SIN);
    osc4.SetWaveform(osc.WAVE_SIN);
    
    osc.SetFreq(200);
    osc.SetAmp(0.1);
    osc2.SetFreq(400);
    osc2.SetAmp(0.1);
    osc3.SetFreq(600);
    osc3.SetAmp(0.1);
    osc4.SetFreq(800);
    osc4.SetAmp(0.11);

    // start callback
    hw.StartAudio(AudioCallback);


    while(1) {}
}

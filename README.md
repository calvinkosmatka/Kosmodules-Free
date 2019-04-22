# Kosmodules
## Free Modules
### OSFx2
![OSFx2](gh_res/osf.png)
OSFx2 is a dual offsetter, attenuverter (with gain), and full-wave rectifier with switchable order, and CV control of all parameters.

###### IN
Signal (audio or CV) in.
###### OUT
Mangled signal out.
###### ORD
Order of Offsetting, Scaling, and Folding. Default order is Offset->Scale->Fold. Order is indicated by the lights next to the CV jacks for OFT, SCL, and FLD (green->yellow->red). Button cycles the order. Jack accepts a trigger pulse to cycle the order.
###### OFT
Offset summed with output of previous stage. Knob ranges from -10.0 to 10.0. CV input is summed with knob value.
###### SCL
Scaling factor multiplied with output of previous stage. Knob ranges from -10.0 to 10.0. CV is summed with knob value.
###### FLD
Full-wave rectification applied to output of previous stage. Button toggles off and on. Jack accepts a trigger pulse to toggle off and on.

## Paid Modules
### Distributions
![Distributions](gh_res/distributions.png)
Distributions is a probability distribution-governed randomness source, with dual OSF built in and a display of the distribution post-OSF.
###### TRG
Triggers a sample from the current distribution. Jack accepts a trigger pulse.
###### RES
Reseeds the internal random number generator, allowing you to produce repeatable sequences. If you've found a sequence you like, you are free to offset, scale, and fold it, but changing the distribution, and its parameters, P1 and P2, may disturb the sequence. Jack accepts a trigger pulse.
###### DIS
Cycles the currently selected distribution. P1 and P2 knob values are saved when cycling through distributions. Jack accepts a trigger to cycle through distributions.
###### P1
First parameter of curent distribution. Knob ranges from -10.0 to 10.0. CV is summed with knob value and clamped to -10.0 to 10.0.
###### P1
Second parameter of curent distribution. Knob ranges from -10.0 to 10.0. CV is summed with knob value and clamped to -10.0 to 10.0.
#### Distributions
Distributions currently has three built in distributions: Gaussian (normal/bell-curve), Gamma, and Beta.
##### Gaussian
###### P1
Mean. Ranges from -10.0 to 10.0.
###### P2
Variance. Knob+CV -10.0 to 10.0 maps to 0.0 to 20.0.
##### Gamma
###### P1
Kappa. Knob+CV -10.0 to 10.0 maps to 0.001 to 20.001.
###### P2
Theta. Knob+CV -10.0 to 10.0 maps to 0.001 to 20.001.
##### Beta
###### P1
Alpha. Knob+CV -10.0 to 10.0 maps to 0.001 to 20.001.
###### P2
Beta. Knob+CV -10.0 to 10.0 maps to 0.001 to 20.001.
#### OSF
Two OSFs are applied to the sampled value. With the default parameters, these have no effect. In addition to the usual FLD settings, FLD includes a mirroring mode which rectifies, then inverts with probability .5. See [OSF](#osfx2) for reference.
### Strings
![Strings](gh_res/strings.png)
Strings is an 8-step fractalline gate/dual-CV sequencer, based on the [Cantor set](https://en.wikipedia.org/wiki/Cantor_set).
###### GAT
Controls if given step is active at the 'zero-iteration' level. 
###### CV{X}
CV value for corresponding step. Knob ranges from -5.0 to 5.0.
###### TRG
External trigger input to step through sequence. Overrides internal clock when connected. Jack accepts trigger pulses.
###### RUN
Sets internal clock to run or not. Internal clock runs if button turned on, or CV input is greater than 1V.
###### CLK
'Zero-iteration' clock speed. Effective clock speed is multiplied by LEN<sup>ITR</sup>. Knob ranges from 15 steps/min to 3840 steps/min, scaled exponentially. CV jack overrides knob, is scaled exponentially, and is not clamped, allowing slower or faster clock speeds. At the audio rate, CV outputs turn into oscillators.
###### LEN
Number of steps to include in fractal generation. Ranges from 1 to 8, but 1 isn't very interesting.
###### ITR
'Depth' of the fractal. Each iteration shrinks and copies the top-level 'zero-iteration' sequence into the space of each active step at the previous depth. Fully CCW (at the 'zero-iteration'), Strings is a normal 8-step sequencer. Up to five iterations are allowed.
###### RES
Resets the internal step counter to zero. CV jack accepts a trigger.
###### UIS
Controls whether CV values are updated on inactive steps. This parameter controls behavior of both CV channels.
###### TLT{X}
Governs how CV values are decided for iterated steps. Fully CCW, uses 'zero-iteration' value. Fully CW, uses current-iteration value. In the middle, mixes the values for all intermediate iterations.
###### GATOUT
Sends a 10V gate at each active step.
###### CV{X}OUT
CV output.
###### MSTOUT
Sends a 10V pulse at each 'zero-iteration' step (even inactive steps).
###### RESOUT
Sends a 10V pulse at the zero step.

#### About
Kosmodules is a collection of VCV Rack Modules developed and maintained by Calvin Kosmatka. 

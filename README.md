# juce-template
The aim of this project is to create a template plugin that contains common features that exist across plugins. The implementation tries to handle "Everything but the processing". In short, it handles all the other stuff your plugin should need besides DSP, whether that be audio or MIDI. The project includes a script written in python that can be used to generate a new JUCE project from the template. 

## Components
The project contains a few different components that I found useful.
### Testing
This folder contains sample audio files, a python and Max8 prototype, and a coq file for verification. There is also a python script that can be used to verify the prototype matches the implementation. These files aren't necessarily needed but I found them useful to include.
### Implementation
The implementation contains the following features.
- audio block to manipulate signal or midi
- Rust DSP
- User Interface heirarchy + LookAndFeel
- reactjs user interface
- parameters that can be programmatically initialized
- save and load parameters
- create/load parameter presets; share params via website
- parameter controllers (slider, button, etc)
- key registration
- right click component to bring up sub menu (link to website for manual)
- A/B to switch between presets fast
- save presets in whatever folder you want!
- right click context menu

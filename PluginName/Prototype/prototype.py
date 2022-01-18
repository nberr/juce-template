
import numpy as np       # numerical computations
import scipy as sp       # scientific computation
from scipy.io import wavfile
import matplotlib as mpl # visualizations
import math
import random

def main():
    
    Fs, x = wavfile.read('test.wav') # read the wave file
    x = np.array(x, dtype=float)     # convert data to floats
    
    # TODO: replace 32767 with the sample rate Fs?
    # x = np.divide(x, 32767)          # nomalize to range -1 -> 1
    x = np.divide(x, Fs) # nomalize to range -1 -> 1
    
    N = len(x)
    channels = x.shape[1]
    
    # define plugin parameters here
    
    # output
    y = np.zeros((N, channels))
    
    # main time loop
    # loop can be adjusted depending on the type of processing
    # such as block by block processing, or processing
    # each channel together rather than each sample
    for n in range(N):
        for channel in range(channels):
            sample = x[n][channel]
            
            # process the audio
            
            y[n][channel] = sample
    
    wavfile.write('output.wav', Fs, y)
    

if __name__ == '__main__':
    main()

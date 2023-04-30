import numpy as np
from scipy import signal

# FBCCA：滤波器组设计
passband = [6, 14, 22, 30, 38, 46, 54, 62, 70, 78]
stopband = [4, 10, 16, 24, 32, 40, 48, 56, 64, 72]

def filterbank(eeg, fs, idx_fb):
	Wp = [passband[idx_fb] / (fs / 2), 90 / (fs / 2)]
	Ws = [stopband[idx_fb] / (fs / 2), 100 / (fs / 2)]
	Rp = 3
	Rs = 60
	N, Wn = signal.cheb1ord(Wp, Ws, Rp, Rs)
	bp_R = 0.5
	B, A = signal.cheby1(N, bp_R, Wn, "bandpass")
	y = signal.filtfilt(B, A, eeg)
	return y
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

def find(res_array):
	for item in res_array:
		a = res_array - item
		cnt = np.sum(np.where(a, 0, 1))
		if cnt >= len(res_array) - 1:
			return item
	return 0

def sincosref(list_freqs, fs, num_smpls, num_harms, w_sincos):
	num_freqs = len(list_freqs)
	y_ref = np.zeros((num_freqs, 2 * num_harms, num_smpls))
	t = np.array([(i * 1.0) / fs for i in range(1, num_smpls + 1)])
	# 对每个参考频率都生成参考波形
	for freq_i in range(0, num_freqs):
		tmp = np.zeros((2 * num_harms, num_smpls))
		# harm:harmonic wave 谐波
		for harm_i in range(0, num_harms):
			stim_freq = list_freqs[freq_i]
			# Frequencies other than the reference frequency
			d_sin = np.zeros((num_freqs, num_smpls))
			d_cos = np.zeros((num_freqs, num_smpls))
			for freq_j in range(0, num_freqs):
				if freq_j != freq_i:
					d_freq = list_freqs[freq_j]
					d_sin[freq_j, :] = np.sin(
						2 * np.pi * (harm_i + 1) * d_freq * t)
					d_cos[freq_j, :] = np.cos(
						2 * np.pi * (harm_i + 1) * d_freq * t)
			temp_d_sin = np.sum(d_sin, 0)
			temp_d_cos = np.sum(d_cos, 0)
			# superposition of the reference frequency with other frequencies
			tmp[2 * harm_i] = (np.sin(2 * np.pi * (harm_i + 1)
							   * stim_freq * t) + w_sincos * temp_d_sin)
			tmp[2 * harm_i + 1] = (np.cos(2 * np.pi * (harm_i + 1)
								   * stim_freq * t) + w_sincos * temp_d_cos)
		y_ref[freq_i] = tmp

	return y_ref
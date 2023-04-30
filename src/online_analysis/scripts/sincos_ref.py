import numpy as np

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
                    d_sin[freq_j, :] = np.sin(2 * np.pi * (harm_i + 1) * d_freq * t)
                    d_cos[freq_j, :] = np.cos(2 * np.pi * (harm_i + 1) * d_freq * t)
            temp_d_sin = np.sum(d_sin, 0)
            temp_d_cos = np.sum(d_cos, 0)
            # superposition of the reference frequency with other frequencies
            tmp[2 * harm_i] = (np.sin(2 * np.pi * (harm_i + 1) *stim_freq * t) + w_sincos * temp_d_sin)
            tmp[2 * harm_i + 1] = (np.cos(2 * np.pi * (harm_i + 1) *stim_freq * t) + w_sincos * temp_d_cos)
        y_ref[freq_i] = tmp

    return y_ref

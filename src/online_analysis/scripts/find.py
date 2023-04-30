import numpy as np
def find(res_array):
    for item in res_array:
        a = res_array - item
        cnt = np.sum(np.where(a, 0, 1))
        if cnt >= len(res_array) - 1:
            return item
    return 0
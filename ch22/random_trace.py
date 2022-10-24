import numpy as np

# seed random number generator
np.random.seed(1)
# generate some integers
values = np.random.randint(0, 10, 20)
print(values)

# trace with locality using 80-20 workload
values_80 = np.random.randint(0, 2, 16)
values_20 = np.random.randint(2, 10, 4)
values_local = np.append(values_80, values_20)
np.random.shuffle(values_local)
print(values_local)

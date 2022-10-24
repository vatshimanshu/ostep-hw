import matplotlib.pyplot as plt

x = [4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000]
y = [6000, 6000, 6000, 6000, 50, 50, 50, 50]

plt.title('TLB size measurement')
plt.ylabel('Bandwidth of accessing memory in MB/s')
plt.xlabel('size of memory allocated in MB')
plt.plot(x, y, marker=".", markersize=15)
plt.show()

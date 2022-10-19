import matplotlib.pyplot as plt

x = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048]
y = [3, 2, 3, 3, 6, 15, 19, 22, 19, 20, 21, 21]

plt.title('TLB size measurement')
plt.ylabel('time per access (ns)')
plt.xlabel('Number of pages')
plt.semilogx(x, y, marker=".", markersize=15, base=2)
plt.show()
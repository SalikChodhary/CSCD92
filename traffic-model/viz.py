import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('traffic_data.txt')

num_steps = data.shape[0]
num_cars = data.shape[1] // 2

reshaped_data = data.reshape(num_steps, num_cars, 2)

plt.figure(figsize=(10, 6))
for i in range(num_cars):
    plt.scatter(reshaped_data[:, i, 0], reshaped_data[:, i, 1], s=1, marker='.')
plt.xlabel('Position')
plt.ylabel('Time')
plt.title('Nagel-Schreckenberg Traffic Simulation')
plt.show()

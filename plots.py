from matplotlib import pyplot as plt
import csv
import pandas as pd

df = pd.read_csv('cmake-build-debug/src/jacobi_performance.csv')

df2 = pd.read_csv('cmake-build-debug/src/jacobi_without_optimization_performance.csv')
df3 = pd.read_csv('cmake-build-debug/src/lu_performance.csv')

plt.grid()
plt.plot('matrix_size', 'whole_time', color='blue', data=df)
plt.plot('matrix_size', 'hot_loop_time', color='red', data=df)

plt.plot('matrix_size', 'whole_time', color='green', data=df2)
plt.plot('matrix_size', 'hot_loop_time', color='orange', data=df2)


plt.plot('matrix_size', 'whole_time', color='pink', data=df3)
plt.plot('matrix_size', 'hot_loop_time', color='yellow', data=df3)
plt.legend()
plt.show()
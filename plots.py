from matplotlib import pyplot as plt
import csv
import pandas as pd

df = pd.read_csv('mybuild/jacobi_performance.csv')

df2 = pd.read_csv('mybuild/gauss_seidel_performance.csv')
df3 = pd.read_csv('mybuild/lu_performance.csv')
df4 = pd.read_csv('mybuild/jacobi_without_optimization_performance.csv')

plt.grid()
# plt.plot('matrix_size', 'whole_time', color='blue', data=df)
plt.plot('matrix_size', 'hot_loop_time', label='jacobi_optimized', data=df)


# plt.plot('matrix_size', 'whole_time', color='green', data=df2)
plt.plot('matrix_size', 'hot_loop_time', label='gauss-seidel', data=df2)


# plt.plot('matrix_size', 'whole_time', color='pink', data=df3)
plt.plot('matrix_size', 'hot_loop_time', label='lu decomposition', data=df3)

plt.plot('matrix_size', 'hot_loop_time', label='jacobi', data=df4)
plt.legend()
plt.show()
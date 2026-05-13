#!/usr/bin/env python3
import re
import matplotlib.pyplot as plt

with open('docs/collisions.txt') as f:
    collisions = f.read()

sizes = list(map(int, re.findall(r'Размер данных:\s+(\d+)', collisions)))
N = list(map(int, re.findall(r'Коллизий:\s+(\d+)', collisions)))

plt.figure()
plt.plot(sizes, N, 'o-')
plt.xlabel('Размер массива')
plt.ylabel('Число колллизий')
plt.grid()
plt.yscale('log')
plt.savefig('docs/collision_plot.png')
plt.show()
#!/usr/bin/env python3
import re
import matplotlib.pyplot as plt

with open('docs/collisions.txt') as f:
    data_coll = f.read()

sizes = list(map(int, re.findall(r'Размер данных:\s+(\d+)', data_coll)))
collisions = list(map(int, re.findall(r'Коллизий:\s+(\d+)', data_coll)))

with open('docs/times_with_fill.txt') as f:
    data_time_1 = f.read()

linear = list(map(float, re.findall(r'Линейный поиск:\s+([\d.]+)', data_time_1)))
tree_1 = list(map(float, re.findall(r'бинарного дерева:\s+([\d.]+)', data_time_1)))
hash_1 = list(map(float, re.findall(r'хэш-таблицы:\s+([\d.]+)', data_time_1)))
rbtree_1 = list(map(float, re.findall(r'красно-черного дерева:\s+([\d.]+)', data_time_1)))
mm_1 = list(map(float, re.findall(r'std::multimap:\s+([\d.]+)', data_time_1)))


with open('docs/times_no_fill.txt') as f:
    data_time_2 = f.read()

tree_2 = list(map(float, re.findall(r'бинарного дерева:\s+([\d.]+)', data_time_2)))
hash_2 = list(map(float, re.findall(r'хэш-таблицы:\s+([\d.]+)', data_time_2)))
rbtree_2 = list(map(float, re.findall(r'красно-черного дерева:\s+([\d.]+)', data_time_2)))
mm_2 = list(map(float, re.findall(r'std::multimap:\s+([\d.]+)', data_time_2)))

fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(15, 5))

ax1.plot(sizes, collisions, 'o-', color='red')
ax1.set_xlabel('Размер массива')
ax1.set_ylabel('Число коллизий')
ax1.grid(True)
ax1.set_title('Коллизии хеш-функции')

ax2.plot(sizes, linear, 'o-', label='Линейный')
ax2.plot(sizes, tree_1, 's-', label='Бинарное дерево')
ax2.plot(sizes, rbtree_1, '^-', label='Красно-черное дерево')
ax2.plot(sizes, hash_1, 'd-', label='Хеш-таблица')
ax2.plot(sizes, mm_1, 'v-', label='std::multimap')
ax2.set_xlabel('Размер массива')
ax2.set_ylabel('Время (мс)')
ax2.grid(True)
ax2.set_yscale('log')
ax2.set_title('Время (построение + поиск)')
ax2.legend()

ax3.plot(sizes, linear, 'o-', label='Линейный')
ax3.plot(sizes, tree_2, 's-', label='Бинарное дерево')
ax3.plot(sizes, rbtree_2, '^-', label='Красно-черное дерево')
ax3.plot(sizes, hash_2, 'd-', label='Хеш-таблица')
ax3.plot(sizes, mm_2, 'v-', label='std::multimap')
ax3.set_xlabel('Размер массива')
ax3.set_ylabel('Время (мс)')
ax3.grid(True)
ax3.set_yscale('log')
ax3.set_title('Время только поиска')
ax3.legend()

plt.tight_layout()
plt.savefig('docs/plot.png')
plt.show()
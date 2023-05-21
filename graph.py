import matplotlib.pyplot as plt
  

left = [1, 2]

height = [23] * 2
  

tick_label = ['AVL tree', 'Red-Black tree']
  

plt.bar(left, height, tick_label = tick_label,
        width = 0.5, color = ['red', 'green'])
  

plt.xlabel('Trees')
plt.ylabel('Height')
plt.title('Tree\'s Height')
plt.show()
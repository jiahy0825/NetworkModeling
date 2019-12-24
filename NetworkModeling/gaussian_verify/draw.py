import matplotlib.pyplot as plt

fd = open('data.txt', 'r')
li = []
for line in fd.readlines():
	li.append(float(line))
print(len(li))
plt.hist(li, bins=100, color='steelblue', density=True)
plt.show()
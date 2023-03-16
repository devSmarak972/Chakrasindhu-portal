from windrose import WindAxes
import matplotlib.pyplot as plt
import sys
import numpy as np
# print('Number of arguments: {}'.format(len(sys.argv)))
# print('Argument(s) passed: {}'.format(str(sys.argv)))

from windrose import WindroseAxes
wd = []
ws = []
for i in range(1000):
    y = np.random.randint(360)
    wd.append(y)
    ws.append(np.random.randint(1, 20))
    # print(y)

ax = WindroseAxes.from_ax()
ax.bar(wd, ws, normed=True, edgecolor="white", bins=np.arange(1, 8, 0.5))
ax.set_legend()
# ax.savefig("figs/wrdaily"+sys.argv[1]+".jpg")
plt.savefig('./public/figs/windrose/daily'+sys.argv[1]+'.jpg')
plt.close()


ax = WindAxes.from_ax()
bins = np.arange(0, 7 + 1, 0.5)
bins = bins[1:]
ax, params = ax.pdf(ws, bins=bins)
plt.savefig('./public/figs/weibull/daily' +
            sys.argv[1]+"_"+str(params[1])+"_"+str(params[3])+'.jpg')
plt.close()
print(params)

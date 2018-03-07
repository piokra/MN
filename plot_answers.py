from matplotlib.pyplot import *

import fileinput
from math import tan


splitLines = list((map(float, line.split()) for line in fileinput.input()))
x, y = zip(*splitLines)
plot(x, y)
show()
yp = list(map(lambda x: tan(x), x))
diff = list(map(lambda x: abs(x[0]-x[1]), zip(y, yp)))
plot(x, diff)
show()
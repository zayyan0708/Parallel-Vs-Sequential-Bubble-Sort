import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from pathlib import Path

f=open("SortingTime.txt",mode="r");
z=f.readline();
print(z);
x=f.readline()
print(x)
c=f.readline();
a=str(c)
print(c)
d='0'

# x-coordinates of left sides of bars
left = [0,2,4]
 
# heights of bars
height = [d,x, c]
 
# labels for bars
tick_label = [z]
 
# plotting a bar chart
plt.bar(left, height, tick_label = tick_label,
        width = 1.5, color = ['red', 'green','blue'])
 
# naming the x-axis
plt.xlabel('Size of Data')
# naming the y-axis
plt.ylabel('Time Taken')
# plot title
plt.title('Green=Parallel Blue=Serial')
 
# function to show the plot
plt.show()

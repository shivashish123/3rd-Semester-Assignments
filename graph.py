import matplotlib.pyplot as plt 
  
# line 1 points 
x1 = [1000000,2000000,3000000,4000000,5000000] 
y1 = [216064,449552,691723,936701,1193598] 
# plotting the line 1 points  
plt.plot(x1, y1, label = "thread") 
  
# line 2 points 
x2 = [1000000,2000000,3000000,4000000,5000000]
y2 = [221699,458490,700657,946864,1205543] 
# plotting the line 2 points  
plt.plot(x2, y2, label = "process") 
  
# naming the x axis 
plt.xlabel('Number of elements in array (N)') 
# naming the y axis 
plt.ylabel('Time in micro-seconds') 
# giving a title to my graph 
plt.title('Time of Process Creation Vs Thread Creation') 
  
# show a legend on the plot 
plt.legend() 
  
# function to show the plot 
plt.show() 
		
		
		
		
		
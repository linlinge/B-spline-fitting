clear
clc
close all
x=-2:0.01:8;
n=length(x);
y=zeros(1,n);
p=2;
m=4;
KnotVector=0:(m+p);
for i=1:length(x)
    y(i)=BaseFunction(1,m,x(i),KnotVector);
end
plot(x,y)
close all
clear
clc
KnotVector=[0 0 0 1 2 3 3 3];
x=-1:0.01:6;
n=length(x);
xb=zeros(1,n);
yb=zeros(1,n);
k=3;
P=[0 2;1 0;3 2;5 0;6 2];

for i=1:n
    for j=1:length(P)
        xb(i)=xb(i)+P(j,1)*BaseFunction(j,k,x(i),KnotVector);
        yb(i)=yb(i)+P(j,2)*BaseFunction(j,k,x(i),KnotVector);
    end
end
index=find(xb==0);
index(1)=[];
xb(index)=[];
yb(index)=[];
plot(xb,yb)
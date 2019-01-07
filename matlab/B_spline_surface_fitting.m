close all
clear
clc
%% init
m=4;
x=0:0.1:10;
y=x;
n=length(x);

[xs,ys]=meshgrid(x,y);
z=zeros(n,n);
for i=1:n
    for j=1:n
        z(i,j)=sin(x(i))+sin(y(j));
    end
end
mesh(x,y,z)

%%

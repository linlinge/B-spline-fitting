close all
clear
clc
%% init
m=4;
x=[0:0.1:10]';
y=tan(x);
h=length(x); % number of raw data, assume number of control points = h
n=h;
KnotVector=zeros(1,n+m+1);
for i=1:n+m+1
    if  i<= m
        KnotVector(i)=0;
    elseif i>= m+1 && i<=n+1
        KnotVector(i)=i-m;
    else
        KnotVector(i)=n-m+2;
    end
end

%KnotVector=1:(h+m); % N+m
%% 
N=zeros(n-1,h-1);
for i=1:n-1
    for j=1:h-1
      N(i,j)=BaseFunction(j,m,x(i),KnotVector);
    end
end

N(1,:)=[];
N(end,:)=[];

Q=zeros(h-1,1);
for i=1:h-1
    sum=0;
    for j=1:n-1
        sum=sum+ BaseFunction(j,m,x(i),KnotVector)*y(i);
    end
    Q(i,1)=sum;
end


temp=inv(N'*N);
Px=temp*x(2:end);
Py=temp*Q;
% plot(x,y,'r')
% hold on
plot(Px,Py,'g');



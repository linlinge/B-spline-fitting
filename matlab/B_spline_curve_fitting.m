close all
clear
clc
%% init
m=4;
x=[-2:0.1:10]';
y=sign(x);
h=length(x); % number of raw data
n=h; % number of control points


% KnotVector=zeros(1,n+m);
% for i=1:n+m
%     if  i<= m
%         KnotVector(i)=0;
%     elseif i>= m+1 && i<=n+1
%         KnotVector(i)=i-m;
%     else
%         KnotVector(i)=n-m+2;
%     end
% end

KnotVector=[zeros(1,m-2) x(1):(x(end)-x(1))/(n-1):x(end) ones(1,3)*x(end)];
%KnotVector=1:(h+m); % N+m
%% 
N=zeros(n,h);
for i=1:n
    for j=1:h
      N(i,j)=BaseFunction(j,m,x(i),KnotVector);
    end
end

temp=inv(N'*N);

Q=y;


Py=inv(N'*N)*N'*Q;
plot(x,y,'r')
hold on
plot(x,Py,'g');
%plot(x(10:end),Py(10:end),'g');

norm(Py(10:end-10)-y(10:end-10))



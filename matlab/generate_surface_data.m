close all
clear
clc


delta_x=0.025;
delta_y=0.025;

x=-0.8:delta_x:0.8;
y=x;

[X,Y]=meshgrid(x,y);
Z=sin(6*X)-cos(6*Y);
mesh(X,Y,Z)


f=fopen('../data/saddle.txt','w+');
fprintf(f,'%f %f %f\n',x(1),delta_x,x(end));
fprintf(f,'%f %f %f\n',y(1),delta_y,y(end));
for i=1:length(X)
    for j=1:length(X)
        fprintf(f,'%f %f %f\n',X(i,j),Y(i,j),Z(i,j));
    end
end
fclose(f);
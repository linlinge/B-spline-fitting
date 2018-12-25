close all
clear
clc

x=-10:10;
y=x;

[X,Y]=meshgrid(x,y);
Z=X.^4-Y.^4;
mesh(X,Y,Z)


f=fopen('../data/saddle.txt','w+');
for i=1:length(X)
    for j=1:length(X)
        fprintf(f,'%f %f %f\n',X(i,j),Y(i,j),Z(i,j));
    end
end
fclose(f);
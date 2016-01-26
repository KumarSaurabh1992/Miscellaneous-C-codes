clear all;
clc;


load solver.txt
load size_mat.txt
m = size_mat(1);
n = size_mat(2);
X = zeros(n,m);
k = 1;
for i = 1:n
    for j = 1:m
        X(i,j) = solver(k);
        k = k + 1;
    end
end

contourf(X);
colorbar;

        